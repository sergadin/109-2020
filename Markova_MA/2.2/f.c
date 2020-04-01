#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define eps 0.00001
#define T 1000
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

double integral(double (*f)(double), double a, double b, ErrorCode *perr)
{
	
	double h = (b - a)/2, I1 = 0, I2;
	int check = 0;
	I2 = (ab(b - a)*h)/2;
	if(a >= b)
	{
		*perr = INT_ND;
		return I2;
	}
	while(ab(I1 - I2) > eps)
	{
		check++;
		if(check > T)
		{
			*perr = INT_NOT;
			return I1;
		}
		I1 = I2;
		I2 = 0;
		h /= 2;
		for(double h1 = a; h1 <= b; h1 += h)
		{
			I2 += (*f)(h1) + (*f)(h1 + h);
		}
		I2 *= h/2;
	}
	*perr = INT_OK;
	return I2;
}

