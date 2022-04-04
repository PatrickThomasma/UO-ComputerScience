#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

float g(float *a,int n){   //For B
   float prod = 1.0f;
   int i=0;
   for(i=0;i<n;i++){        //0 is not checking here
           prod*= a[i];  
   }
}
float f(float *a,int n){    // For A
      float prod = 1.0f;
      int i=0;
      for(i=0;i<n;i++){
           if(a[i]!=0.0f)
               prod*= a[i];  
   	}
}
float *createArray(int size)	{     // Array function
      float *a=(float *)malloc(sizeof(float));
      int i=0;
      for(i = 0; i < size; i++){
          float r=rand()/(float)RAND_MAX;
          a[i]=r< 0.5f ? 0.0f:r+0.26f;
   }
      return a;
}
int main(){
	struct timeval start, end;//This is for time calculation
	int i=0;
	int k=0;
	float *a=createArray(10000);//A array creation
	float *b=createArray(10000);//B array

	float *c=(float*)malloc(sizeof(float));//C array
	gettimeofday(&start, NULL);

	float data=f(a,10000);
	gettimeofday(&end, NULL);

	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	printf("f() took %lf seconds to execute \n", time_taken); //Calculating the time for F()
	gettimeofday(&start, NULL); //Time start

	float data2=g(b,10000);
	gettimeofday(&end, NULL); //Time Stop

	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6; //Calculating the time for G()
	printf("g()for B took %f seconds to execute \n", time_taken);

//FOR C PART

	for(i=0;i<1000;i++){
   		if(b[i]!=0.0f)
       			c[k++]=b[i];
       		}
        gettimeofday(&start, NULL);

	float data3=g(c,k-1);
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	printf("g() for C took %f seconds to execute \n", time_taken); //Time for g() for C
	gettimeofday(&start, NULL);

	float data4=f(c,k-1);
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	printf("f() for C took %f seconds to execute \n", time_taken); //Time for f() for C
	free(b);//Deallocating memory
	free(a);//Deallocating memory
	free(c);//Deallocating memory
//The reason that this is the case is because since c is only processing the 1.0f data it'll not only be a shorter
//array but the time to run it will be faster since there are less elements to parse through and they
//will not be as random as the initial arrays were for the original two functions that are ran through.
	return 0;
	}
