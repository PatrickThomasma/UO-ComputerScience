#include <stdio.h>

long loop(long a,long b) {
	long result = 0; //result is both edx and rdx
	// rci which is b is moved inot rcx which is also cl in 8 bit
	for (long mask = 1; mask != 0; mask <<= b) { //rax and eax is mask which =1 
		// mask != 0 since testq compares mask to 0
		// mask <<= b because of cl at above
		result |= (a & mask); //r8 is rax
		//rdi and edi is argument 1
		//rsi and esi is argument 2
		//then iteration
	}
	//movq to rax is used
	return result;
}


int main() {
	long x = loop(1,5);
	printf("%ld\n",x);
	x = loop(2,4);
	printf("%ld\n",x);
	x = loop(3,3);
	printf("%ld\n",x);
	x = loop(4,2);
	printf("%ld\n",x);
	x = loop(5,1);
	printf("%ld\n",x);
	return 0;
}
