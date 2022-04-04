#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void inner (float *u, float *v, int length, float *dest) {
	int i;
	float sum = 0.0f;
	for (i = 0; i < length; ++i) {
		sum += u[i] * v[i];
	}
	*dest = sum;
}

void inner2 (float *u, float *v, int length, float *dest) {
	int i;
	int limit = length - 3;
	float sum = 0.0f;
	float sum1 = 0.0f;
	float sum2 = 0.0f;
	float sum3 = 0.0f;
	for (i = 0; i < limit; i += 4) {
		sum += u[i] * v[i];
		sum1 += u[i+1] * v[i+1];
		sum2 += u[i+2] * v[i+2];
		sum3 += u[i+3] * v[i+3];
	}
	for (;i < length; i++) {
		sum += u[i] * v[i];
	}
	*dest = sum + sum1 + sum2 + sum3;
}
int main () {
	float * u = (float*)malloc(sizeof(float) * 50000);
	float * v = (float*)malloc(sizeof(float) * 50000);
	for (int i = 0; i < 50000; i++) {
		u[i] = 1;
		v[i] = 1;
	}
	float test1;
	clock_t start = clock();
	inner(u,v,50000,&test1);
	clock_t finish = clock();
	double test1_time = (double)(finish - start);
	printf(" Inner() takes : %f\n",test1);
	printf(" Time taken to run inner() : %f\n",test1_time);

	float test2;
	clock_t start1 = clock();
	inner2(u,v,50000,&test2);
	clock_t finish1 = clock();
	double test2_time = (double)(finish1 - start1);
	printf("Inner2() result: %f\n", test2);
	printf("Time taken to run inner2(), %f\n",test2_time);

	return 0;

}


