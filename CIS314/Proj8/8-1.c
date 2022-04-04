#include <stdio.h>
#include <stdlib.h>

struct Line {
	unsigned char data[4];
	unsigned int tag;
	unsigned char valid;
};
struct Cache {
	struct Line *lines;
	int numLines;
};

unsigned int getOffset (unsigned int address) {
	return address & 0x3;
}

unsigned int getSet (unsigned int address) {
	return (address >> 2) & 0xF;
}

unsigned int getTag (unsigned int address) {
	return address >> 6;
}

struct Cache* mallocCache(int numLines) {
	struct Cache *cache = malloc(sizeof(struct Cache));
	cache->numLines = numLines;
	cache->lines = (struct Line *)malloc(sizeof(struct Line) * numLines);
	for (int i = 0; i < numLines; i++) {
		cache->lines[i].valid = 0;
	}
	return cache;
}

void freeCache (struct Cache *cache) {
	free(cache->lines);
	free(cache);
}

void printCache(struct Cache *cache) {
	int length = cache->numLines;
	for (int i = 0; i < length; i++) {
		struct Line *line = &cache->lines[i];
		if (line->valid == 1){
			unsigned char *data = line->data;
			printf("set %x - tag: %x -valid: 1 - data: %.2x %.2x %.2x %.2x\n",i,line[i].tag, data[0], data[1], data[2], data[3]);
		}
	}
}

void readValue (struct Cache *cache, unsigned int address) {
	unsigned int s = getSet(address);
	unsigned int t = getTag(address);
	unsigned int o = getOffset(address);
	struct Line *line = &cache->lines[s];
	printf("looking for set: %x -tag: %x\n",s,t);

	if (line->valid == 1) {
		unsigned char *data = line->data;
		printf("found set: %x - tag: %x -offset: %x - valid: 1 - data: %.2x\n", s, line->tag,o, data[0]);
		if (line->tag != t)
			printf("Tags dont match, miss!\n");
		else
			printf("hit!\n");
	} else {
		printf("no valid line found - miss!\n");
	}
}
void writeValue(struct Cache *cache, unsigned int address, unsigned char *newData) {
	unsigned int s = getSet(address);
	unsigned int t = getTag(address);
	struct Line *line = &cache->lines[s];
	if (line->valid && line->tag != t) {
		unsigned char *data = line->data;
		printf("evicting line -set: %x - tag: %x - valid: %u - data: %.2x %.2x %.2x %.2x\n", s ,line->tag,line->valid,data[0],data[1],data[2],data[3]);
	}
	for (int i = 0; i < 4; ++i) {
		line->data[i] = newData[i];
	}
	line->tag = t;
	line->valid = 1;
	printf("wrote set: %x - tag: %x - valid: %u - data: %.2x %.2x %.2x %.2x\n",s , line->tag, line->valid, newData[0], newData[1], newData[2], newData[3]);
}

int main() {
	struct Cache *cache = mallocCache(16);
	char c;
	do {
		printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: ");
		scanf(" %c", &c);
		if (c == 'r') {
			printf("Enter 32-bit unsigned hex address: ");
			unsigned int a;
			scanf(" %x", &a);
			readValue(cache, a);
		} else if (c == 'w') {
			printf("Enter 32-bit unsigned hex address: ");
			unsigned int a;
			scanf(" %x", &a);

			printf("Enter 32-bit unsigned hex value: ");
			unsigned int v;
			scanf(" %x", &v);

			unsigned char *data = (unsigned char *) &v;

			writeValue (cache, a, data);
		} else if (c == 'p') {
			printCache(cache);
		}
	} while (c != 'q');
	freeCache (cache);
}



