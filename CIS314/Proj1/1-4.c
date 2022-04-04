#include <stdio.h>
void printBytes(unsigned char *start, int len) {
 	for (int i = 0; i < len; ++i) {
 		printf(" %.2x", start[i]);
 		}	
        printf("\n");
}


void printInt(int x) {

	printBytes((unsigned char *) &x, sizeof(int));
	//prints out 04 00 00 00 
	//prints out 4 bytes for the int data type
 }
void printFloat(float x) {
	printBytes((unsigned char *) &x, sizeof(float));
	//print outs 00 00 80 40
	//float is 4 bytes which is what is printed out 
	}
void printShort(short x) {
	printBytes((unsigned char *)&x, sizeof(short));
	// prints out 04 00
	// prints out two bytes that short data type produces 
}
void printLong(long x) {
	// print outs 04 00 00 00 00 00 00 00 
	// while a long is 8 bytes since I am on a 64 bit machine the printout
	// will be 8 bytes
	printBytes((unsigned char *)&x, sizeof(long));
}
void printLongLong(long long x) {
	//prints out 04 00 00 00 00 00 00 00 
	//a long long is 8 bytes so 8 bytes are printed by its size
	printBytes((unsigned char *)&x, sizeof(long long));
}
void printDouble(double x) {
	//prints out 00 00 00 00 00 00 00 10 40
	//a double is 8 bytes which is why the result is 8 numbers
	printBytes((unsigned char *)&x, sizeof(double));
}

//behavior of bytes are printed out according to the data types, any weird variances are shown by the difference of the 64 to 32 bit systems.

int main() {
	int x = 4;
	printInt(x);
	printFloat(x);
	printShort(x);
	printLong(x);
	printLongLong(x);
	printDouble(x);
	return 0;
}
