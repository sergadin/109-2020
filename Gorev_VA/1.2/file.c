#include <stdio.h>
#include "root.h"

double one(double x);
double one(double x)
{
	return 1.0 + 0.0*x;
}

double func(double (*f)(double));
double func(double (*f)(double))
{
	return 2.0 * (*f)(1.0);
}

double F1(double x);
double F1(double x)
{
	return x*x - 1.0;
}

double F2(double x);
double F2(double x)
{
	return 1.0/256.0 * x*x*x*x - 4.0;
}

double F3(double x);
double F3(double x)
{
	return 1.0/(x*x*x) - 2.0;
}

int main(void)
{
	printf("%f\n", root(F1, 0.0, 2.0));
	printf("%f\n", root(F2, -6.0, -2.0));
	printf("%f\n", root(F3, 0.5, 2.0));
	return 0;
}
