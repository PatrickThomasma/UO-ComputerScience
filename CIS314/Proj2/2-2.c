#include <stdio.h>

int extract( int x, int y) {
	int shift = y << 3; //shift y over to grab significance
	int replaces = 0b11111111 << shift; //shift over mask to place
	int masker = x & replaces; // mask the original hex with
	int lost = masker >> shift;
	int changed = lost << 24;
	int work = changed >> 24;
	return work;

}



int main() {
	int a = 0xABCDEF00;
	int i = 3;
	int conclusion = extract(a,i);
	printf("%X\n",conclusion);
	return 0;
}
