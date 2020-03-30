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
	printf("f(x) = x^2 - 1 at [0, 2]\n calculated root: %f\n actual root:    %f\n", root(F1, 0.0, 2.0), 1.0);
	printf("f(x) = 1/256 x^4 - 4 at [-6, -2]\n calculated root: %f\n actual root:    %f\n", root(F2, -6.0, -2.0), -5.6568542495);
	printf("f(x) = 1/x^3 - 2 at [0.5, 2]\n calculated root: %f\n actual root:    %f\n", root(F3, 0.5, 2.0), 0.7937005293);
	return 0;
}
