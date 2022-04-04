#include <stdio.h>
#include <stdlib.h>

int sum (int x) {
	if (x <= 1) {
		return x;
	}
	return x + sum(x-1);
}

int main() {
	int value = sum(5);
	return 0;
}
