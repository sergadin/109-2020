#include <stdio.h>
#include "sum.h"
double o(double x);
double f(double x);
double z(double x);
double modul(double x);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
int main(void)
{
	int i, n = 4, m = 3;
	double array[] = {1, 1, 5, 9}, result;
	double b[] = {0, 4, 16};
	double e = 0.000000000000000000000000000000000001;
	double k = 0;
	double l = 0;
	RRFUN funcs[] = {z, o, f};
	for(i = 0; i < m; i++)
	{
		result = sum(funcs[i], array, n);
		if (modul(result - b[i]) < e*MAX1(result, b[i], 1))
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

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
double z(double x)
{
	x *= 1;
	return 0;
}
double f(double x)
{
	return x;
}
double o(double x)
{
	x *= 1;
	return 1;
}

