#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void bufset(char *buf, char  c, int len) {
	for (int i = 0; i < len; i++) {
		buf[i] = c;
	}
}
int HasWord (char *txt, char *word) {
	int i,p,t;
	int occ = 0;
	int check;
	int a = strlen(word);
	for (i = 0; txt[i] != '\0'; i++) {
		char *name = malloc(80);
		bufset(name ,0 ,a);
		size_t len = strlen(name);
		if (txt[i] == word[0]) {
			for (t = 0,p = i; t != a; t++,p++) {
				name[len++] = txt[p];
				name[len] = '\0';
			}
			check = strncmp(name, word, a);
			if (check == 0 ) {
				if (i == 0)
					occ++;
				else if  ((txt[i-1] - '@' <  0) && (txt[i + a] - '@' < 0))
					occ++;
			}
		
		}
		free(name);

		}
		return occ;
		}
int main (int argc, char *argv[]) {
	int i = 2;
	int occ;
	FILE *fp;
	char* word;
	char *txt;
	long int buff_size;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "%s is not a valid file. \n",argv[1]);
		return 1;
	}
	fseek(fp,0,SEEK_END);
	buff_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	txt = malloc(1048);
	bufset(txt,0,1048);
	fread(txt,sizeof(char),buff_size+1,fp);
	fclose(fp);
	if (i < argc) {
		while (i < (argc)) {
			word = argv[i];
			occ = HasWord(txt,word);
			printf("The word \"%s\" occurs %d times.\n",word, occ);
			i++;
		}
	}
	free(txt);
	return 0;
}
