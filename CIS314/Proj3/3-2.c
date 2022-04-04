#include <stdio.h>
long f(long x, long y, long z) {
	z = y + z;
	x = x + z;
	z <<= 63;
	z >>= 63;
	int a = x;
	return z ^ a;
}

int main () {
	long num = f(10,20,30);
	printf("Number is %ld", num);
	return 0;

}
