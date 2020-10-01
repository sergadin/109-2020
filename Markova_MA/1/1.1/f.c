#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
double ab (double m) 
{
	if(m < 0)
	{
		return -m;
	}
	else
	{
		return m;
	}
}
double root(double (*f)(double), double a, double b, double eps, ErrorCode *perr)
{
	double m = (a + b)/2;
	if(perr != NULL)
	{
        *perr = ROOT_OK;
		if((*f)(a)*(*f)(b) >= 0)
		{
			*perr = ROOT_NOT;
			return m; 
		}
	}
	if((*f)(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	while(ab(b - a) < eps)
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

