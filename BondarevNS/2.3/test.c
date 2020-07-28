#include <stdio.h>
#include <math.h>
#include "simp.h"
double f1(double a);
double f2(double a);
double f3(double a);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double eps = 0.0001, a = 0.1, b = 2, result = 0;
	double e = 0.0001;
	double correct[] = {4.220700, 88.166333, 64.316594};
	RRFUN fun[] = {f1, f2, f3};
	for(i = 0; i < 3; i++)
	{
		result = integ(a, b, eps, fun[i]);
		if (result > 10000000000)
		{
			printf("OK\n");
			printf("0\n");
			return 0;
		}
		if (fabs(result - correct[i]) < e*MAX1(result, correct[i], 1))
		{
			printf("OK\n");
			printf("%lf\n", result);
		}
		else
		{
			printf("NO_OK\n");
			printf("%lf\n", result);
		}
	}

	return 0;
}

double f1(double a)
{
	double k = (sqrt(6 - a));
	return k;
}

double f2(double a)
{
	double k = a*a + 45;
	return k;
}

double f3(double a)
{
	double k = log(a)+34;
	return k;
}


