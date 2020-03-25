#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simpson.h"

double simp(double a, double b, double ep, RRFUN ffunc)


{
	int n = 2, i;
	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0, i1 = 0, i2 = 0;
	while (n > 0)
	{
		res1 = 0, res2 = 0;
		h = (b-a)/(2*n);
		for(i = 1; i < n-1; i++)
		{
			x = a+2*i*h;
			res1 = res1 + (*ffunc)(x);
		}
		for(i = 1; i < n; i++)
		{
			x = a+(2*i-1)*h;
			res2 = res2 + (*ffunc)(x);
		}
		i1 = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));
		
		res1 = 0, res2 = 0;
		n = n*2;
		h = (b-a)/(2*n);
		for(i = 1; i < n-1; i++)
		{
			x = a+2*i*h;
			res1 = res1 + (*ffunc)(x);
		}
		for(i = 1; i < n; i++)
		{
			x = a+(2*i-1)*h;
			res2 = res2 + (*ffunc)(x);
		}
		i2 = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));

		if (modul(i2 - i1) <= ep)
		{
			res = i2;
			break;	
		}
	}
	return res;
}


double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

