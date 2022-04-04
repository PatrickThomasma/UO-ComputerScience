#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
struct intArray {
	int length;
	int *dataPtr;

};

struct intArray* mallocIntArray(int length) {
	struct intArray* Array = malloc(sizeof(struct intArray));
	if (Array == NULL)
		return NULL;
	Array->length = length;
	// Set array variables equal to length/malloced of the size of an int
	Array->dataPtr = malloc(length *sizeof(int));
	if (Array -> dataPtr == NULL) {
		free(Array);
		return NULL;
	}
	return Array;
}
void readIntArray(struct intArray *arrayPtr) {
	int data;
	char numstr[20];
	char *num;
	long temp;
	int i = 0;
	// this for loop wil go through the whole array  and start inserting numbers as given by the user into the array
	for (i = 0; i<arrayPtr->length;i++) {
		printf("Enter int: ");
		scanf("%s",numstr);
		temp = strtol(numstr, &num, 10);
		if (strlen(num) > 0) {
			printf("Invalid input\n");
			i--;
			continue;
		}
		data = temp;
		arrayPtr->dataPtr[i]= data;
	}
}

void swap (int *xp, int *yp) {
	int temp = *xp;
	*xp = *yp;
	//basic swap function as showed in class
	*yp = temp;
}

void sortIntArray(struct intArray *array) {
	// basic sort function found online on geekforgeeks
	int i,j;
	for (i = 0; i < array->length-1;i++) {
		for (j = 0; j <array->length-i-1; j++) {
			if (array->dataPtr[j] > array->dataPtr[j+1])
				swap(&array->dataPtr[j], &array->dataPtr[j+1]);
		}
	}
}

void printIntArray(struct intArray *array) {
	printf(" [ ");
	int i;
	// for loop through the array and print all the inputs one by one
	for (i = 0; i < array->length; i++){
		printf("%d",array->dataPtr[i]);
	}
	printf(" ] ");
}
void freeIntArray(struct intArray *array) {
	int i = 0;
	free(array->dataPtr);
	free(array);
}

int main() {
	int size;
	char numstr[100];
	char *ptr = NULL;
	long temp;
	// while loop that'll keep going on forever until return statement is hit
	while (1) {
		printf("Enter Length : ");
		scanf("%s",&numstr);
		temp = strtol(numstr,&ptr,10);
		if (strlen(ptr) > 0) {
			printf("invalid input");
			continue;
		}
		size = temp;
		//run all the functions and create the array
		struct intArray *myArray = mallocIntArray(size);
		readIntArray(myArray);
		sortIntArray(myArray);
		printIntArray(myArray);
		freeIntArray(myArray);
		return 0;
	}
	return 0;
}
