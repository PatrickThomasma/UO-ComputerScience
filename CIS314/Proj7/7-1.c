#include <stdio.h>

unsigned int getOffset (unsigned int address) {
	unsigned int mask = 0x000000FF;
	return address & mask;
}
unsigned int getSet(unsigned int address) {
	unsigned int mask = 0x0000000F;
	return (address >> 8) & mask;
}
unsigned int getTag (unsigned int address) {
	return address >> 12;
}

int main() {
	unsigned int addr = 0x12345678;
	printf("0x%X: offset: %X -tag %X -set: %X\n", addr,getOffset(addr),getTag(addr), getSet(addr));
	addr = 0x87654321;
	printf("0x%X: offset: %X -tag %X -set: %X\n", addr,getOffset(addr),getTag(addr), getSet(addr));
	return 0;
}

