#include <stdio.h>

#include "sum.h"
double f1 (double x)
{
	return x*x + 5*x - 6;
}
double f2 (double x)
{
	return x*x + 1;
}
double f3 (double x)
{
	return x*x*x;
}
double f4 (double x)
{
	return x*x + 5*x;
}
int main(void)
{
	double a = -4, b = 2, eps = 0,0001;
	if(f1(a)*f1(b) >= 0 || f2(a)*f2(b) >= 0 || f3(a)*f3(b) >= 0 || f4(a)*f4(b) >= 0)
	{
		printf("FAULT");
	}
	if(f1(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	root(f1, a, b, eps);
	if(f2(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	root(f2, a, b, eps);
	if(f3(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	root(f3, a, b, eps);
	if(f4(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	root(f4, a, b, eps);
	return 0;
}


