#include <stdio.h>

void shift_right(unsigned int word) {
	printf("%X\n",word >> 2);

}
void shift_left(unsigned int word) {
	printf("%X\n",word << 2);
}

int main() {
	shift_left(0xABCDEF01);
	shift_right(0xABCDEF01);
	return 0;

	//explanation for shift right is that the word will be shifted to the right two times and the binary numbers to the very right will be dropped
	//explanation for the shift left is that the word will be shifted to the left and two 0's will be added to the front of it.
