#include "root.h"
#define eps 0.000001

double derivative(double (*f)(double), double x)
{
	return ((*f)(x + eps / 2.0) - (*f)(x)) / (eps / 2.0);
}


double root(double (*f)(double), double a, double b)
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
	while (1)
	{
		//printf("%f\n", derivative(f, b));
		c = b - (*f)(b) / derivative(f, b);
		//printf("b %f\n", c);
		if ((c > b) || (c < a))
		{
			c = a - (*f)(a) / derivative(f, a);
			//printf("a %f\n", c);
			if (((b - a) < (eps)) || ((c - a) < (eps)))
				break;
			else
				a = c;
		}
		else
			if (((b - a) < (eps)) || ((b - c) < (eps)))
				break;
			else
				b = c;
	}
	return c;
}
