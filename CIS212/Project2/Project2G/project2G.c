#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void bufset(char *buf, char c, int len) {
	for (int i = 0; i < len; i++) {
		buf[i] = c;
	}
}
void BinRead(char *matrix, FILE *new) {
	int num = 0;
	int i = 0;
	while (i !=  16) {
		fprintf(new,"%d\n",matrix[num]);
		i++;
		if ((i % 4) == 0)
			num = num + 36;
		else
			num = num + 4;
	}
}

int main (int argc, char *argv[]) {
	// File processing initilization 
	int i = 1;
	FILE *fp;
	char *txt;
	FILE *new;
	long int buff_size;
	fp = fopen(argv[1], "r");
	//if fp has nothing then its not valid
	if (fp == NULL) {
		fprintf(stderr, "%s is not a valid file.\n",argv[1]);
		return 1;
	}
	fseek(fp,0,SEEK_END);
	buff_size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	txt = malloc(1048);
	bufset(txt,0,1048);
	fread(txt, sizeof(char), buff_size+1,fp);
	fclose(fp);
	if (i < argc) {
		new = fopen(argv[i+1], "w"); 
		BinRead(txt,new);
		i++;
		free(txt);
		fclose(new); 
		return 0;
	}
	free(txt);
	return 0;
}
