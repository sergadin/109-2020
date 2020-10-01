#include <stdio.h>
#include <math.h>
#include "root.h"

double findRoot(double a, double b, double epsilon, RRFUN f)
{
	while(fabs(b - a) > epsilon)
	{
		a = b - (b - a) * (*f)(b) / ((*f)(b) - (*f)(a));
		b = a + (a - b) * (*f)(a) / ((*f)(a) - (*f)(b));
	}

	return b;
}