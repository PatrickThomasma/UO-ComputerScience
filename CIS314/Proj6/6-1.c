#include <stdio.h>

int f(int a, int b, int c, int d, int n) {
	int result = 0;
	int old =  a * b;
	int new = c * d;
	int result2 = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			result += result2 + j + old;
		}
		result2 += new;
	}
	return result;
}


int main () {
	int a = 5;
	int b = 4;
	int c = 3;
	int d = 2;
	int e = 1;
	int result =f(a,b,c,d,e);
	printf("%d\n",result);
	return 1;
}
