#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

double root(double (*f)(double), double a, double b, double eps)
{
	double m = (a + b)/2;
	while((b - a) < eps)
	{
		if((*f)(m) < 0)
		{
			a = (*f)(m);
		}
		else
		{
			b = (*f)(m);
		}
		m = (a + b)/2;
	}
	return m;
}
void all (double (*f)(double), double a, double b, double eps)
{
	if((*f)(a)*(*f)(b) >= 0)
	{
		printf("FAULT");
	}
	if((*f)(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	m = root(f, a, b, eps);
	printf("Answer = %e\n", m);
}
