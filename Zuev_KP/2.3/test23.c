#include <stdio.h>
#include <math.h>
#include "func.h"
double func(double a, double b);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	double ep = 0.0001, a = -2, b = 4, result = 0, otvet = 36, k = 0;
	double e = 1e-4;
	k = rung(a, b, ep, func);
	result = simp(a, b, k, func);
	if (modul(result - otvet) < e*MAX1(result, otvet, 1))
	{
		printf("пройден\n");
	}
	else
	{
		printf("не пройден\n");
	}
	printf("%lf\n", result);
	printf("%lf\n", k);
	return 0;
}

double func1(double a, double b)
{
	double k = b*(8+2*a-a*a);
	return k;
}

double func2(double a, double b)
{
	double k = b*(8+2*a-a*a);
	return k;
}

