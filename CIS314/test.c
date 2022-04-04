#include <stdio.h>
#include <stdlib.h>
int absdiff(int x,int y) {
	int result;
	if ( x > y){
		goto GREATER;
		}
	goto DONE;
GREATER:
	result = x - y;
DONE:
	return y - x;
}
int main () {
	int check = 5;
	int result = 7;
	int x = absdiff(7,5);
	printf("%d\n",x);
	return 0;
}
