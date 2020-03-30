#include <stdio.h>
#include "sum.h"

double abcf(RRFUN f, double x)
{
	if ((*f)(x) < 0)
	{
		return -(*f)(x); 
	}
	else
	{
		return (*f)(x);
	}
}
double root(RRFUN f, double a, double b, double eps);
{
	double m = (a + b)/2;
	while(b - a < eps)
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
