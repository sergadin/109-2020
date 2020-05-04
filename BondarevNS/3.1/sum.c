#include <stdio.h>
#include <math.h>
#include "sum.h"

double Findmin(double h, double x, double epsilon, RRFUN f)
{
	if (x==0)
	{ 
		x = x + 0.1;
	}
	while (((f(x+h)-2*f(x)+f(x-h))/(h*h)) <= 0)
	{ 
		x = x + 0.1;
	}
	double x1;
        x1=x-0.5*h*(f(x+h)-f(x-h))/(f(x+h)-2*f(x)+f(x-h));
        while (fabs(x1-x)>epsilon) 
		{
			x=x1;
        		x1=x-0.5*h*(f(x+h)-f(x-h))/(f(x+h)-2*f(x)+f(x-h));
    		}
	
	return x1;
}

