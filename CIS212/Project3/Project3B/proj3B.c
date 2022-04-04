#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct
{
	int num_elements;
	double elements[MAX_STACK_SIZE];
}Stack;

void Initialize (Stack *s)
{
	s->num_elements = 0;

}

void push(Stack *s, double x) {
	s->elements[s->num_elements] = x;
	s->num_elements++;

}

double pop (Stack *s){
	double rv;
	for (int i = 0; i < s->num_elements; i++) 
		rv = s->elements[i];
	s->num_elements--;
	return rv;
}
void IssueError(){
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
double CalculateFraction(char *str) {
	int i = 1;
	double num = 0.0;
	char ch;
	int error = 0;
	double div = 1.0;
	int hey;
	while ((ch = str[i]) !=  '\0') {
		if ((ch - '0') > 10)
			IssueError();
		if (ch == '.')
			IssueError();
		if (str[i] == '-')
			IssueError();
		num = num * 10 + (ch - '0');
		i++;
		hey = i;}
	for (int t = 1; t < hey; t++) 
		div = div * 10;
	num = num / div;
	return num;
}
double StringToDouble(char *str){
	int i = 0;
	double v = 0;
	char ch;
	double t;
	double ret = 0.0;
	while ((ch = str[i]) != '\0'){
		if (str[i] == '-') {
			i++;
			continue;
		}
		if (str[i] == '-' && i > 0)
			IssueError();
		if ((ch - '0') > 10) 
			IssueError();
		if (str[i] == '.'){
			v = CalculateFraction(str+i);
			break;
		}
		ret = ret*10 + (ch-'0');
		i++;
	}
	if (str[0] == '-') {
		return -(ret + v);
	}
	
    return (ret + v);
}
void main(int argc, char *argv[]){
    int i = 1;
    double pat;
    Stack s;
    Initialize(&s);
    if (i < argc) {
	    while (i < argc) {
		 double v = 0;
		 double t = 0;
		 if (argv[i][0]  == '+') {
			v = pop(&s);
			t = pop(&s);
			t = t + v;
			push(&s, t);
		}
		 else if  (argv[i][0] == 'x') {
			v = pop(&s);
			t = pop(&s);
			t = t * v;
			push(&s,t);
		}
		 else if (argv[i][0] == '-') {
			v = pop(&s);
			t = pop(&s);
			t = t - v;
			push(&s,t);
		}
		 
		else {
			v = StringToDouble(argv[i]);
			push(&s,v);
	    }
		i++;
   }

    }

	    pat = pop(&s);
	    printf("The total is %.03f\n",pat);
}
