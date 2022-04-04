#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ColorPoint {
	int a,r,g,b;
};

struct ColorPoint** create2DArray (int n) {
	// Array to hold a pointer to the beginning of each row
	struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
	for (int i = 0; i < n; ++i) {
		points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
		for (int j = 0; j < n; ++j) {
			points[i][j].a = rand();
			points[i][j].r = rand();
			points[i][j].g = rand();
			points[i][j].b = rand();
		}
	}
	return points;
}
void free2DArray (struct ColorPoint**points, int n) {
	for (int i = 0; i < n; ++i) {
		free(points[i]);
	}
	free(points);
}

long f (struct ColorPoint**points, int n) {
	long sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += points[j][i].a;
			sum += points[j][i].r;
			sum += points[j][i].g;
			sum += points[j][i].b;
		}
	}
	return sum;
}

long g (struct ColorPoint**points, int n) {
	long sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += points[i][j].a;
			sum += points[i][j].r;
			sum += points[i][j].g;
			sum += points[i][j].b;
		}
	}
	return sum;
}

int main() {
	struct ColorPoint **points = create2DArray(2048);
	long value;
	double time_taken;
	clock_t t;
	t = clock();
	value = f(points,2048);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("f() took %f seconds to execute \n", time_taken);
	t = clock();
	value = g(points,2048);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("g() took %f seconds to execute \n", time_taken);

	return 0;
}


