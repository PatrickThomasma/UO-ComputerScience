#include <stdio.h>
unsigned int replace(unsigned int x, int i, unsigned char b) {
	// x is 10010010
	//  & 11000000
	//  00111111
	// b is 11
	// i is 011 
	// now i is 011000
	// 1100000000000000000000000
	// masking is & 11111111 put 24 0's in front shift it by shift
	// then mask the result there
	// 11110000 ~ 00001111
	int shift = i << 3;
	int shifter = b << shift;
	int replacer = 0b11111111 << shift;
	int masker = x & ~replacer;
	int result = shifter | masker;
	return result;

}



int main() {
	unsigned int a = 0x12345678;
	int i = 2;
	unsigned char b = 0xAB;
	int finish;
	finish = replace(a,i,b);
	printf("%X\n",finish);
	return 0;

}
