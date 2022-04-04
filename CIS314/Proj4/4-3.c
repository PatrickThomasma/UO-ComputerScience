#include <stdio.h>
long fact(long x) {// pop is called here to check the next x
	if (x <= 1) { //cmpq assembly checking if statement
		return 1; //jumpts to .L8 if if statement fails if not then movl1 to eax then return (ret)
	} 
	long px = x; //push rbx into stack will move movq into rbx
	long fx = fact(x-1);  // call fact is performed 
	return px * fx; 
}


int main() {
	long x = fact(5);
	printf("%ld\n",x);
	 x = fact(5);
	printf("%ld\n",x);
	 x = fact(6);
	printf("%ld\n",x);
	 x = fact(7);
	printf("%ld\n",x);
	return 0;



}


