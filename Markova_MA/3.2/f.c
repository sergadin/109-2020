#include"f.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <math.h>

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
double gold(double (*f)(double), double a, double b, double eps, ErrorCode *perr)
{
	int check = 1;
    double phi, x1, x2;
    phi = (1 + sqrt(5))/2;
    x1 = b - (b - a)/phi;
    x2 = a + (b - a)/phi;
    if((*f)(x1) >= (*f)(x2))
    {
		a = x1;
    }
	else
    {
		b = x2;
    }
	while (fabs(b - a) >= eps)
    {
		x1 = b - (b - a)/phi;
		x2 = a + (b - a)/phi;
		if( (a <= x1 || x1 <= a) && (b >= x2 || x2 >= b) )
		{
			if((*f)(x1) >= (*f)(x2))
			{
				a = x1;
			}
			else
			{
				b = x2;
			}
		}
		else
		{
			return(x1);
			break;
		}
		if(check > T)
		{
			*perr  = ER;
			return 0;
		}
		//printf("%d\n", check);
		//printf("%e\n", b - a);
		check++;
    }
	*perr  = OK;
	//printf("%e\n", (b + a)/2);
	if(ab(b - a) >= eps)
	{
		*perr  = ER;
		return 0;
	}
	printf("%e\n", (a + b)/2);
	x2 = (a + b)/2;
    double f1, f2, f3, u;
	if(*perr)
	{
		printf("tut\n");
		return 0;
	}
	f3 = (*f)(b);
	f1 = (*f)(a);
	f2 = (*f)(x2);
	u = x2 - ((x2 - a) * (x2 - a) * (f2 - f3) - (x2 - b) * (x2 - b) * (f2 - f1)) / ((x2 - x1) * (f2 - f3) - (x2 - b) * (f2 - f1)) * 0.5;
	//printf("%e\n", u);
	if(u < a || b < u)
	{
		*perr = ER;
		return 0;
	}
	if((*f)(u) > (*f)(x2))
	{
		return (*f)(x2);
	}
	else
	{
		return (*f)(u);
	}
}
