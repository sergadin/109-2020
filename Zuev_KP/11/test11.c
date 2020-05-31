#include <stdio.h>
#include <math.h>
#include "11.h"
double func1(double t, double x);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double ep = 0.00001, a = 0, b = 11, result = 0;
	double e = 0.00001;
	double c[] = {16.6504};
	RRFUN funcs[] = {func1};
	for(i = 0; i < 1; i++)
	{
		result = integrate(a, b, ep, funcs[i]);
		if (modul(result - c[i]) < e*MAX1(result, c[i], 1))
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

double func1(double t, double x)
{
	double k = (x-t)/(sqrt(1+t*t*t*t));
	return k;
}










