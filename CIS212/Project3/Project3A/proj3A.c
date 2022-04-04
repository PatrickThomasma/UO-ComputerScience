#include <stdio.h>
#include <stdlib.h>

/* struct definitions go here.
 * use:
 *  typedef struct
 *  {
 *     ...
 *  } Apple;  (or Banana or Fruit)
 */


typedef struct Apple {

	int green;
	double radius;

}Apple;

typedef struct Banana{
	double radius;
	double height;
}Banana;

typedef struct Fruit  {
	void *self;
	char*(*GetColor)(void *);
	double (*GetVolume)(void *);

}Fruit;

char* FruitGetColor(Fruit *f) {
	return f->GetColor(f->self);
}

double FruitGetVolume(Fruit *f) {
	return f->GetVolume(f->self);
}
char* AppleGetColor(void *Ap) {
	Apple *pat = (Apple *)Ap;
	if (pat->green) 
		return "green";
	else
		return "red";

}
char* BananaGetColor(void *b) {
	Banana *pat = (Banana*)b;
	return "yellow";
}
double AppleGetVolume(void *a) {
	Apple *pat = (Apple *)a;
	return 4/ 3.0*pat->radius*pat->radius*pat->radius*3.14;
}
double BananaGetVolume(void *B) {
	Banana *pat = (Banana *)B;
	return pat->height * pat->radius * pat->radius * 3.14;
}

Fruit *CreateApple(double r, int isGreen)
{
	Apple *a = malloc(sizeof(Apple));
	a->radius = r;
	a->green = isGreen;
	Fruit *f = malloc(sizeof(Fruit));
	f->self = a;
	f->GetColor = AppleGetColor;
	f->GetVolume = AppleGetVolume;
	return f;
}
/* DO NOT MODIFY BELOW THIS POINT */
/* (ALTHOUGH YOU CAN MODIFY FOR TESTING PURPOSES ... JUST CHANGE IT BACK) */

Fruit *CreateBanana(double r, double h)
{
    Banana *a = malloc(sizeof(Banana));
    a->radius = r;
    a->height = h;
    Fruit *f = malloc(sizeof(Fruit));
    f->self = a;
    f->GetColor = BananaGetColor;
    f->GetVolume = BananaGetVolume;
    return f;
}
int main()
{
    Fruit *f1 = CreateApple(0.2, 0);
    Fruit *f2 = CreateApple(0.4, 1);
    Fruit *f3 = CreateBanana(0.5, 2);
    Fruit *f4 = CreateBanana(0.4, 3);

    printf("Fruit 1 is %s and has volume %f\n", FruitGetColor(f1), FruitGetVolume(f1));
    printf("Fruit 2 is %s and has volume %f\n", FruitGetColor(f2), FruitGetVolume(f2));
    printf("Fruit 3 is %s and has volume %f\n", FruitGetColor(f3), FruitGetVolume(f3));
    printf("Fruit 4 is %s and has volume %f\n", FruitGetColor(f4), FruitGetVolume(f4));
}
