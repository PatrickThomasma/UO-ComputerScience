#include <stdio.h>
#include <stdlib.h>
#define N 4
typedef long array_t[N][N];

void transpose(array_t a) {

	long int t1 = 0;
	long int t2 = 0;
	for (int i = 0; i < N; ++i) {
		long int *i1 = &a[i][0];
		long int *j1 = &a[0][i];
		for (int k = 0; k < i; ++k) {
		t1 = *i1;
		t2 = *j1;
		*i1 = t2;
		*j1 = t1;
		i1 += 1;
		j1 += 4;
		}
	}
}
/*
void transpose (array_t a) {
	for (long i = 0; i < N; ++i) {
		for (long j = 0; j < i; ++j) {
			long t1 = a[i][j];
			long t2 = a[j][i];
			a[i][j] = t2;
			a[j][i] = t1;
		}
	}
}
*/
int main ()
{
	int a;
	long int array_t[4][4];
	long int i;
	long int j;
	printf("Enter N: ");
	scanf("%d", &a);
	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++)
		{
			printf("Enter Array: ");
			scanf("%ld",&array_t[i][j]);

		}
	}
	transpose(array_t);
	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++) {
			printf("%ld ,",array_t[i][j]);
		}
	}
	return 0;
}
