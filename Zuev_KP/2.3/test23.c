#include <stdio.h>
#include <math.h>
#include "func.h"
double func1(double a, double b);
double func2(double a, double b);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double ep = 1e-100, a = -2, b = 4, result = 0, k = 0;
	double e = 1e-4;
	double c[] = {36, 1.78244};
	RRFUN funcs[] = {func1, func2};
	for(i = 0; i < 2; i++)
	{
		k = rung(a, b, ep, funcs[i]);
		result = simp(a, b, k, funcs[i]);
		if (modul(result - c[i]) < e*MAX1(result, c[i], 1))
		{
			printf("пройден\n");
		}
		else
		{
			printf("не пройден\n");
		}
	}

	return 0;
}

double func1(double a, double b)
{
	double k = b*(8+2*a-a*a);
	return k;
}

double func2(double a, double b)
{
	double k = b*sin(a*a+a-100);
	return k;
}
