#include <stdio.h>

//Code to figure out all composite numbers from a range of 1-500
int main(){
	int i,n,j;
	for (i = 10; i <= 500; i++) {
		int factor = 1;
		if (i % 2 != 0) {
			for (n = 2; n != i; n++) {
				if (i % n == 0) {
					factor++;
				}
			}
		}
	if (factor > 1)
	{
		printf("%d is a composite number.\n",i);
		}


	
	}
	return 0;

}



