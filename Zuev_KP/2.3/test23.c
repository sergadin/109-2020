#include <stdio.h>
#include <math.h>
#include "func.h"
double func(double a, double b);
double sum(double a, double b);


int main(void)
{
	double n = 1000, a = -2, b = 4, result = 0;
	result = simp(a, b, n, func, sum);
	printf("%lf\n", result);
	return 0;
}

double func(double a, double b)
{
    double k = b*(8+2*a-a*a);
    return k;
}
double sum(double a, double b)
{
    return a+b;
}


