#include <stdio.h>
int mask(int x) {
	unsigned int a = 0b11111111111111111111111111111111;
	int shifter = 32 - x;
	unsigned int solution = a >> shifter;
	return solution;


}

int main () {
	int x = 31;
	unsigned int conclusion = mask(x);
	printf("%X\n",conclusion);
	return 0;
}
