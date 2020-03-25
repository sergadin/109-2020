#include <stdio.h>
#include <math.h>
#include "simpson.h"
double func1(double a);
double func2(double a);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double ep = 0.00001, a = -2, b = 4, result = 0, k = 0;
	double e = 0.00001;
	double c[] = {36, 1.78244};
	RRFUN funcs[] = {func1, func2};
	for(i = 0; i < 2; i++)
	{
		k = rung(a, b, ep, funcs[i]);
		result = simp(a, b, k, funcs[i]);
		if (modul(result - c[i]) < e*MAX1(result, c[i], 1))
		{
			printf("пройден\n");
			printf("%lf\n", result);
			printf("%lf\n", k);
		}
		else
		{
			printf("не пройден\n");
			printf("%lf\n", result);
			printf("%lf\n", k);

		}
	}

	return 0;
}

double func1(double a)
{
	double k = (8+2*a-a*a);
	return k;
}

double func2(double a)
{
	double k = sin(a*a+a-100);
	return k;
}
