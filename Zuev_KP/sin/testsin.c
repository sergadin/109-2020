#include <stdio.h>
#include <math.h>
#include "sin.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double func1(double x);
double modul(double x);

int main(void)
{
	int i;
	double ep = 1e-100, result = 0;
	double e = 0.01;
	double x[] = {3.14/6, 8, 99};
	double b[] = {0.5, 0.1391, 0.9877};
	for(i = 0; i < 3; i++)
	{
		result = taylor(x[i], ep, func1);
		if (modul(result - b[i]) < e*MAX1(result, b[i], 1))
		{
			printf("пройден\n");
			printf("%lf\n", result);
		}
		else
		{
			printf("не пройден\n");
			printf("%lf\n", result);
		}
	}
	return 0;
}

double func1(double x)
{
	double k = sin(x);
	return k;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
