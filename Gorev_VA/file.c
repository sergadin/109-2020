#include <stdio.h>

double one(double x);
double one(double x)
{
	return 1 + 0*x;
}

double func(double (*f)(double x));
double func(double (*f)(double x))
{
	return 2 * (*f)(1);
}

int main(void)
{
	printf("%f", func(one));
	return 0;
}