#include <stdio.h>
#include <math.h>
#include "func.h"
double func(double a, double b);
double sum(double a, double b);


int main(void)
{
	double n = 5, a = 0, b = 5, result = 0;
	result = simp(a, b, n, func, sum);
	printf("%lf\n", result);
	return 0;
}

double func(double a, double b)
{
    double k = b*(a/(a*a*a*a+4));
    return k;
}
double sum(double a, double b)
{
    return a+b;
}


