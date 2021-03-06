#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>

#define NUM_TIMERS  4
#define CREATE_TIME  0
#define READ_TIME  1
#define TRAIN_TIME  2
#define PREDICT_TIME  3

static const int numSamples = 60000;
static const int numTests = 10000;
static const int numInputs = 784;
static const int numHidden1Nodes = 260;
static const int numHidden2Nodes = 80;
static const int numOutputs = 10;
static const int EPOCHS = 10;

static const double lr = 0.01; 

double act(double x) {
	return tanh(x);
}

double act_d(double x) {
	return 1.0 - pow(act(x), 2);
}

double weights_init()
{
	return ((double)rand())/((double)RAND_MAX);
}

int main() {
	//Initialize Timers
	double timer[NUM_TIMERS];
	clock_t start, end;
	for (int i = 0; i < NUM_TIMERS; ++i)
	{
		timer[i] = 0.0;
	}

	printf("Creating and Initializing Arrays...");
	start = clock();
	double** input = (double**)malloc(sizeof(double*) * numSamples);
	#pragma omp parallel for
	for (int i = 0; i < numSamples; ++i)
	{
		input[i] = (double*)malloc(sizeof(double) * (numInputs+1));
	}
	double** test = (double**)malloc(sizeof(double*) * numTests);
	#pragma omp parallel for
	for (int i = 0; i < numTests; ++i)
	{
		test[i] = (double*)malloc(sizeof(double) * numInputs+1);
	}

	//double* layer1 = (double*)malloc(sizeof(double) * numHidden1Nodes);
	double* layer1_bias = (double*)malloc(sizeof(double) * numHidden1Nodes);
	omp_lock_t l1_bias_locks[numHidden1Nodes];
	omp_lock_t l1_weights_locks[numHidden1Nodes][numInputs];
	double** layer1_weights = (double**)malloc(sizeof(double*) * numHidden1Nodes);
	#pragma omp parallel for 
	for (int i = 0; i < numHidden1Nodes; ++i)
	{
		/* code */
		layer1_weights[i] = (double*)malloc(sizeof(double) * numInputs);
		layer1_bias[i] = weights_init();
		omp_init_lock(&l1_bias_locks[i]);
		for (int j = 0; j < numInputs; ++j)
		{
			/* code */
			omp_init_lock(&l1_weights_locks[i][j]);
			layer1_weights[i][j] = weights_init();
		}
	}

	//double* layer2 = (double*)malloc(sizeof(double) * numHidden2Nodes);
	double* layer2_bias = (double*)malloc(sizeof(double) * numHidden2Nodes);
	double** layer2_weights = (double**)malloc(sizeof(double*) * numHidden2Nodes);
	omp_lock_t l2_bias_locks[numHidden2Nodes];
	omp_lock_t l2_weights_locks[numHidden2Nodes][numHidden1Nodes];
	#pragma omp parallel for 
	for (int i = 0; i < numHidden2Nodes; ++i)
	{
		/* code */
		layer2_weights[i] = (double*)malloc(sizeof(double) * numHidden1Nodes);
		layer2_bias[i] = weights_init();
		omp_init_lock(&l2_bias_locks[i]);
		for (int j = 0; j < numHidden1Nodes; ++j)
		{
			/* code */
			omp_init_lock(&l2_weights_locks[i][j]);
			layer2_weights[i][j] = weights_init();
		}
	}

	//double* output = (double*)malloc(sizeof(double) * numHidden2Nodes);
	double* output_bias = (double*)malloc(sizeof(double) * numHidden2Nodes);
	double** output_weights = (double**)malloc(sizeof(double*) * numHidden2Nodes);
	omp_lock_t out_bias_locks[numOutputs];
	omp_lock_t out_weights_locks[numOutputs][numHidden2Nodes];
	#pragma omp parallel for 
	for (int i = 0; i < numOutputs; ++i)
	{
		/* code */
		output_weights[i] = (double*)malloc(sizeof(double) * numHidden2Nodes);
		output_bias[i] = weights_init();
		omp_init_lock(&out_bias_locks[i]);
		for (int j = 0; j < numHidden2Nodes; ++j)
		{
			/* code */
			omp_init_lock(&out_weights_locks[i][j]);
			output_weights[i][j] = weights_init();
		}
	}
	end = clock();
	timer[CREATE_TIME] += ((double) end - start) / CLOCKS_PER_SEC;
	printf("Done\n");


	FILE* f_train = fopen("data/fashion-mnist_train.txt", "r");
	FILE* f_test = fopen("data/fashion-mnist_test.txt", "r");

	// train input
	printf("Reading Training and Test data...");
	start = clock();

	char* line = NULL;
	char* ptr;
	size_t len = 0;
	//first line is labels
	getline(&line, &len, f_train);
	int sample = 0;
	int feature = 0;
	while(getline(&line, &len, f_train) != -1) {
		char* tok = strtok(line, ",");
		//Normalize data except for label
		int inp = (int)atoi(tok);
		input[sample][feature] = inp;
		feature++;
		do {
			tok = strtok(NULL, ",");
			//printf("feature: %d\n", feature);
			if (tok == NULL || sample == numSamples || feature == numInputs+1)
			{
				break;
			}
			inp = (int)atoi(tok);
			input[sample][feature] = (double) inp / 255.0;
			feature++;
		} while(1);
		//printf("sample %d with %d features\n", sample, feature);
		feature = 0;
		sample++;
	}
	free(line);

	// test input
	char* t_line = NULL;
	char* t_ptr;
	size_t t_len = 0;
	//first line is labels
	getline(&t_line, &t_len, f_test);
	int t_sample = 0;
	int t_feature = 0;
	while(getline(&t_line, &t_len, f_test) != -1) {
		char* t_tok = strtok(t_line, ",");
		int t_inp = (int)atoi(t_tok);
		test[t_sample][t_feature] = (double) t_inp / 255.0;
		t_feature++;
		do {
			t_tok = strtok(NULL, ",");
			if (t_tok == NULL || t_sample == numTests || t_feature == numInputs+1)
			{
				break;
			}
			t_inp = (int)atoi(t_tok);
			test[t_sample][t_feature] = (double) t_inp / 255.0;
			t_feature++;
		} while(1);
		//printf("sample %d added with %d features\n", t_sample, t_feature);
		t_feature = 0;
		t_sample++;
	}
	free(t_line);

	end = clock();
	timer[READ_TIME] += ((double) end - start) / CLOCKS_PER_SEC;
	printf("Done\n");

	//train 
	printf("Creating locks and Training Network...\n");
	start = clock();
	for (int m = 0; m < EPOCHS; ++m)
	{
		printf("Epoch: %d/%d\n", m+1, EPOCHS);
		// train samples
		#pragma omp parallel for 
		for (int i = 0; i < numSamples; ++i)
		{
			double layer1[numHidden1Nodes];
			double layer2[numHidden2Nodes];
			double output[numOutputs];
			//pass through first layer
			for (int j = 0; j < numHidden1Nodes; ++j)
			{
				double a = layer1_bias[j];
				for (int k = 1; k < numInputs+1; ++k)
				{
					a += input[i][k] * layer1_weights[j][k-1];
				}
				layer1[j] = act(a);
			}

			//pass through second layer
			for (int j = 0; j < numHidden2Nodes; ++j)
			{
				double a = layer2_bias[j];
				for (int k = 0; k < numHidden1Nodes; ++k)
				{
					a += layer1[k] * layer2_weights[j][k];
				}
				layer2[j] = act(a);
			}

			//pass through output layer
			for (int j = 0; j < numOutputs; ++j)
			{
				double a = output_bias[j];
				for (int k = 0; k < numHidden2Nodes; ++k)
				{
					a += layer2[k] * output_weights[j][k];
				}
				output[j] = act(a);
				//printf("%f\n", output[j]);
			}
			//printf("\n");


			//get error
			double out_err[numOutputs];
			for (int j = 0; j < numOutputs; ++j)
			{
				double err;
				if (input[i][0] == j) {
					err = 2*(output[j]-1)/numOutputs;
				} else {
					err = 2*(output[j]-0)/numOutputs;
				}
				out_err[j] = err * act_d(output[j]);
			}

			//send error through layers

			double h2_err[numHidden2Nodes];
			for (int j = 0; j < numHidden2Nodes; ++j)
			{
				double err = 0.0;
				for (int k = 0; k < numOutputs; ++k)
				{
					err -= out_err[k] * output_weights[k][j];
				}
				h2_err[j] = err * act_d(layer2[j]);
			}

			double h1_err[numHidden1Nodes];
			for (int j = 0; j < numHidden1Nodes; ++j)
			{
				double err = 0.0;
				for (int k = 0; k < numHidden2Nodes; ++k)
				{
					err -= h2_err[k] * layer2_weights[k][j];
				}
				h1_err[j] = err * act_d(layer1[j]);
			}


			//apply weights
			for (int j = 0; j < numOutputs; ++j)
			{
				omp_set_lock(&out_bias_locks[j]);
				output_bias[j] += out_err[j] * lr;
				omp_unset_lock(&out_bias_locks[j]);
				for (int k = 0; k < numHidden2Nodes; ++k)
				{
					omp_set_lock(&out_weights_locks[j][k]);
					output_weights[j][k] += layer2[k] * out_err[j] * lr;
					omp_unset_lock(&out_weights_locks[j][k]);
				}
			}

			for (int j = 0; j < numHidden2Nodes; ++j)
			{
				omp_set_lock(&l2_bias_locks[j]);
				layer2_bias[j] += h2_err[j] * lr;
				omp_unset_lock(&l2_bias_locks[j]);
				for (int k = 0; k < numHidden1Nodes; ++k)
				{	
					omp_set_lock(&l2_weights_locks[j][k]);
					layer2_weights[j][k] += layer1[k] * h2_err[j] * lr;
					omp_unset_lock(&l2_weights_locks[j][k]);
				}
			}

			for (int j = 0; j < numHidden1Nodes; ++j)
			{
				omp_set_lock(&l1_bias_locks[j]);
				layer1_bias[j] += h1_err[j] * lr;
				omp_unset_lock(&l1_bias_locks[j]);
				for (int k = 1; k < numInputs+1; ++k)
				{
					omp_set_lock(&l1_weights_locks[j][k-1]);
					layer1_weights[j][k-1] += input[i][k] * h1_err[j] * lr;
					omp_unset_lock(&l1_weights_locks[j][k-1]);
				}
			}
			//free(layer1);
			//free(layer2);
			//free(output);
		}
	}
	end = clock();
	timer[TRAIN_TIME] += ((double) end - start) / CLOCKS_PER_SEC;
	printf("Done\n");


	//Create Predictions
	printf("Running Test Data through Network...");
	start = clock();
	int correct = 0;
	#pragma omp parallel for reduction(+:correct)
	for (int i = 0; i < numTests; ++i)
	{
		//printf("Test %d: ", i);
		//pass through first layer
		double layer1[numHidden1Nodes];
		double layer2[numHidden2Nodes];
		double output[numOutputs];

		for (int j = 0; j < numHidden1Nodes; ++j)
		{
			double a = layer1_bias[j];
			for (int k = 1; k < numInputs+1; ++k)
			{
				a += test[i][k] * layer1_weights[j][k-1];
			}
			layer1[j] = act(a);
		}

		//pass through second layer
		for (int j = 0; j < numHidden2Nodes; ++j)
		{
			double a = layer2_bias[j];
			for (int k = 0; k < numHidden1Nodes; ++k)
			{
				a += layer1[k] * layer2_weights[j][k];
			}
			layer2[j] = act(a);
		}

		//pass through output layer
		double max = 0.0;
		int idx;
		for (int j = 0; j < numOutputs; ++j)
		{
			double a = output_bias[j];
			for (int k = 0; k < numHidden2Nodes; ++k)
			{
				a += layer2[k] * output_weights[j][k];
			}
			output[j] = act(a);
			if (output[j] > max) {
				max = output[j];
				idx = j;
			}
		}
		if (idx == (int)test[i][0])
		{
			correct += 1;
		}

		//free(layer1);
		//free(layer2);
		//free(output);
	}
	end = clock();
	timer[PREDICT_TIME] += ((double) end - start) / CLOCKS_PER_SEC;
	printf("Done\n");
	printf("\n");
	printf("Accuracy on Test Data: %f\n", correct / (double)numTests);
	printf("\n");


	//Print Times
	printf("Time to Create Data Structures: %f\n", timer[CREATE_TIME]);
	printf("Time to Read in Training and Test Data: %f\n", timer[READ_TIME]);
	printf("Time to Train Weights and Biases of the layers: %f\n", timer[TRAIN_TIME]);
	printf("Time to Predict Results of Test Data: %f\n", timer[PREDICT_TIME]);


	fclose(f_train);
	fclose(f_test);
	for (int i = 0; i < numSamples; ++i)
	{
		/* code */
		free(input[i]);
	}
	free(input);
	for (int i = 0; i < numTests; ++i)
	{
		/* code */
		free(test[i]);
	}
	free(test);
	for (int i = 0; i < numHidden1Nodes; ++i)
	{
		free(layer1_weights[i]);
		omp_destroy_lock(&l1_bias_locks[i]);
		for(int j = 0; j < numInputs;  j++) {
			omp_destroy_lock(&l1_weights_locks[i][j]);
		}
	}
	free(layer1_weights);
	//free(layer1);
	free(layer1_bias);
	for (int i = 0; i < numHidden2Nodes; ++i)
	{
		free(layer2_weights[i]);
		omp_destroy_lock(&l2_bias_locks[i]);
		for(int j = 0; j < numHidden1Nodes;  j++) {
			omp_destroy_lock(&l2_weights_locks[i][j]);
		}
	}
	free(layer2_weights);
	//free(layer2);
	free(layer2_bias);
	for (int i = 0; i < numOutputs; ++i)
	{
		free(output_weights[i]);
		omp_destroy_lock(&out_bias_locks[i]);
		for(int j = 0; j < numHidden2Nodes;  j++) {
			omp_destroy_lock(&out_weights_locks[i][j]);
		}

	}
	free(output_weights);
	//free(output);
	free(output_bias);
}
