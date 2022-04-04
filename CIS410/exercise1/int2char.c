#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc>1){

unsigned char bytes[4];
unsigned long int x;
sscanf(argv[1], "%d", &x); 
printf("The integer value of input: %d\n", x); 

bytes[0] = (x >> 24) & 0xFF;
bytes[1] = (x >> 16) & 0xFF;
bytes[2] = (x >> 8) & 0xFF;
bytes[3] = x & 0xFF;
  
printf("%x %x %x %x\n", (unsigned char)bytes[0],
                        (unsigned char)bytes[1],
                        (unsigned char)bytes[2],
                        (unsigned char)bytes[3]);    

printf("\nThe original input is: %s\n", argv[1]);
  }
}