#include <stdio.h>






void print_binary(unsigned int x) {
	while(x)
	{
		if (x & 1)
			fprintf(stderr, "1");
		else
			fprintf(stderr, "0");
		x >>= 1;
	}
}



unsigned int combine (unsigned int x, unsigned int y) {
	unsigned int binary;
	unsigned int xbinary;
	//mask the x hex with a large enough number to mask everything but the last 8
	xbinary = x & 4294967040;
	// now mask the second hex with just 4 1's
	binary = y & 15;
	int result = xbinary | binary;
	// now combine them to make the new hex decimal. With x taking the priority with the first 6 hexs.
	return result;
}





int main() {
	unsigned int binary;
	int a = 0x12345678;
	int b = 0xABCDEF00;
	binary = combine(a,b);
	printf("%X\n",binary);
	print_binary(binary);
	return 0;
}
