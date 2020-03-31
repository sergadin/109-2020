#include <stdio.h>
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
