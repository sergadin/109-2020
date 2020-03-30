#include <math.h>
#include "root.h"
#define eps 0.000001

double derivative(double (*f)(double), double x)
{
	return ((*f)(x + eps / 2.0) - (*f)(x)) / (eps / 2.0);
}


double root(double (*f)(double), double a, double b, int* Error)
{
	double c;
	if (a > b)
	{
		c = a;
		a = b;
		b = c;
	}
	c = a;
	if ((b - a) < (eps))
		return c;
	for (int i = 1; i <= 1000000; i++)
	{
		c = b - (*f)(b) / derivative(f, b);
		if ((c > b) || (c < a))
		{
			c = a - (*f)(a) / derivative(f, a);
			if ((c > b) || (c < a))
			{
				*Error = 1;
				return c;
			}
			if (((b - a) < eps) || ((c - a) < eps))
				{
					*Error = 0;
					return c;
				}
			else
				a = c;
		}
		else
			if (((b - a) < eps) || ((b - c) < eps))
				{
					*Error = 0;
					return c;
				}
			else
				b = c;
	}
	*Error = 1;
	return c;
}
