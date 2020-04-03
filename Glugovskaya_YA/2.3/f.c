#include "f.h"


double f (double x)
{
	return x*x + 4;
}


double solve (double (*f)(double), double a, double b, int n)
{
	double h = (b - a)/(2*n), s1 = 0, s2 = 4*f(a + h);
	int i;
	for (i = 1; i < n; i++)
	{
		s1 += 2*f(a + 2*i*h);
		s2 += 4*f(a + (2*i+1)*h);
	}
	return (f(a) + f(b) + s1 + s2)*(h/3);
}


