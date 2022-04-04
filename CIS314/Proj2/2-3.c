#include <stdio.h>
void print_binary(unsigned int x) {
        while(x)
        {
                if (x & 1)
                        fprintf(stderr, "1");
                else
                        fprintf(stderr, "0");
                x >>= 1;
        }
}




int le (float x, float y) {
	unsigned int ux = *((unsigned int*) &x);
	printf("%X\n",ux);
	unsigned int uy = *((unsigned int*) &y);
	printf("%X\n",uy);
	unsigned int sx = ux >> 31;
	unsigned int sy = uy >> 31;
	printf("%d\n",sx);
	printf("%d\n",sy);
	ux <<= 1;
	uy <<= 1;
	return ((sx == 0 && sy == 0 && ux <= uy)||(sx == 1 && sy == 1 && ux >= uy) || (sx == 0 && sy == 1 && ux == uy) || (sx == 1 && sy == 0));
}


int main() {
	int x = -1.0f;
	int y = 2.0f;
	int z = le(x,y);
	printf("%d",z);
	return 0;
	}

