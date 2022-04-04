#include <stdio.h>
#include <stdlib.h>

void IssueError()
{
	// Error raised when string has something thats not a digit
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
	// while loop to find out if the numbers after the . are numbers and if so then turn it into the proper decimal place
	while ((ch = str[i]) !=  '\0') {
		if ((ch - '0') > 10)
			IssueError();
		if (ch == '.')
			IssueError();
		if (str[i] == '-')
			IssueError();
		num = num * 10 + (ch - '0');
		i++;
		hey = i;
	}
	for (int t = 1; t < hey; t++) 
		div = div * 10;
	num = num / div;
	return num;

}


double StringToDouble(char *str)
{
	int i = 0;
	double v;
	char ch;
	double ret = 0.0;
	while ((ch = str[i]) != '\0'){
		if (str[i] == '-') {
			i++;
			continue;
		}
		// using ASCII to find out if string is within limits
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
    return ret + v;
}


int main(int argc, char *argv[])
{
	//parsing the argument to acquire the string
    double v = StringToDouble(argv[1]);
    printf("%.03f\n", v);
 
    return 0;

}
