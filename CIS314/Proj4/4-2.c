#include <stdio.h>


long sum (long from , long to) {
	// Declare and initialize result var - *do not modify*
	long result = 0;

	// Ensure that argument *from* is in %rdi,
	// argument *to* is in %rsi, *result* is in %rax - *do not
	// modify*.
	__asm__("movq %0, %%rdi # from in rdi;" :: "r" (from ));
	__asm__("movq %0, %%rsi # to in rsi;" :: "r" (to));
	__asm__("movq %0, %%rax # result in rax;" :: "r" (result));

	//Your x86_64 code goess below - comment each instruction...
	__asm__("movl $0, %eax;"
		".L2:;"
		"addl %edi, %eax;"
		"addl $1, %edi;"
		"cmpl %esi, %edi;"
		"jle .L2;");

	__asm__("movq %%rax, %0 #result in rax;" : "=r" (result ));
	return result;
}
/*
int sum (int from, int to) {
	int result = 0;
LABEL :
	result += from;
	++from;

	if (from <= to) {
		goto LABEL;
	}
	return result;
}
*/
/*
int sum(int from, int to) {
	int result = 0;
	do {
		result += from;
		++from;
	}
	while (from <= to);
	return result;
}
*/

int main () {
	long t = sum(1,6);
	long a = sum(3,5);
	long s = sum(5,3);
	printf("%ld\n",t);
	printf("%ld\n",a);
	printf("%ld\n",s);
	return 0;
}
