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





void logical_ops(int a, int b) {
	printf("a > b %d\n", a > b);
	printf("a < b %d\n", a < b);
	printf("a == b %d\n", a == b);
	printf("a != b %d\n", a != b);
}

void bitwise_op(int a, int b) {
	print_binary(a ^ b);
	printf("above is ^\n");
	print_binary(a | b);
	printf("above is incluse or \n");
	print_binary(a && b);
	printf("above is and function \n");
	printf("\n");
}

int main()
{
	unsigned int bin = 0b00101010;
	print_binary(bin);
	printf("\n");
	print_binary(100);
	printf("\n");
	logical_ops(1,1);
	printf("\n");
	logical_ops(5,10);
	printf("\n");
	bitwise_op(1,2);
	return 0;

}

