#include <stdio.h>
#include <math.h>
#include "func.h"
double func(double a, double b);
double sum(double a, double b);
double modul(double x);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	double n = 1000, a = -2, b = 4, result = 0, otvet = 36;
	double e = 1e-4;
	result = simp(a, b, n, func, sum);
	if (modul(result - otvet) < e*MAX1(result, otvet, 1))
	{
		printf("пройден\n");
	}
	else
	{
		printf("не пройден\n");
	}
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
double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

