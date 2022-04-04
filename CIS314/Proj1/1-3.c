#include <stdio.h>

int oddBit(unsigned int x) {
	//get a number to where you can mask all the odds with evens
	int y = x & 2863311530;
	return !(!y);
	// do naught naught in order to return a 1 for a true result or 0 for false.



}


int main() {
	unsigned int a = 0x55555555;
	int result;
	result = oddBit(a);
	printf("%d\n",result);
	return 0;



}
