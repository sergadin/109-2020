#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define max2(a, b) ((b) > (a) ?  (b) : (a))
#define max3(a, b, c) max2(max2((a),(b)), (c))
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
double i (double (*f)(double), double a, double b, int n)
{
	double I2 = 0, h = (b - a)/n, h1;
	h1 = a + h;
	for(int i = 1; i < n; i++)
		{
			I2 += (*f)(h1);
			h1 += h;
		}
	return (2*I2 + (*f)(a) + (*f)(b))*h/2;
}
double integral(double (*f)(double), double a, double b, ErrorCode *perr, double eps)
{
	double I1 = 0, I2 = 0, state;
	int check = 0, n = 128;
	if(a >= b)
	{
		*perr = INT_ND;
		return I2;
	}
	I2 = i(f, a, b, n);
	while(ab(I1 - I2) > eps && check < T)
	{
		check++;
		n *= 2;
		I1 = I2;
		I2 = I2 = i(f, a, b, n);
		printf("%e\n", I2);
	}
	if(check >= T)
	{
		*perr = INT_NOT;
		return I1;
	}
	*perr = INT_OK;
	return I2;
}

