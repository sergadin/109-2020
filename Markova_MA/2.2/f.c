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

double integral(double (*f)(double), double a, double b, ErrorCode *perr, double eps)
{
	double h = (b - a)/2, I1 = 0, I2, state, h1;
	int check = 0, n = 2;
	I2 = (ab(b - a)*h)/2;
	if(a >= b)
	{
		*perr = INT_ND;
		return I2;
	}
	state = ((*f)(a) + (*f)(b))/2;
	while(ab(I1 - I2) > eps && check < T)
	{
		check++;
		I1 = I2;
		I2 = 0;
		h /= 2;
		h1 = a + h;
		for(int i = 1; i < n; i++)
		{
			I2 += (*f)(h1);
			h1 += h;
		}
		I2 = (I2 + state)*h;
		n *= 2;
	}
	if(check >= T)
	{
		*perr = INT_NOT;
		return I1;
	}
	*perr = INT_OK;
	return I2;
}

