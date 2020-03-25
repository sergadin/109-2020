#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"func.h"

double simp(double a, double b, double n, RRFUN ffunc)


{
	int i;
	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0;
	h = (b-a)/(2*n);
	for(i = 1; i < n-1; i++)
	{
		x = a+2*i*h;
		res1 = res1 + (*ffunc)(x);
	}
	for(i = 1; i < n; i++)
	{
		x = a+(2*i-1)*h;
		res2 = res1 + (*ffunc)(x);
	}
	res = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));
	return res;
}


double rung(double a, double b, double ep, RRFUN ffunc)
{
	int i;
	double k = 0, n = 2, i1 = 0, i2 = 0; 
	for (i = 1; i < n; i++)
	{
		i1 = simp(a, b, (n/2), ffunc);
		i2 = simp(a, b, n, ffunc);
		if (modul(i2 - i1) <= ep)
		{
			k = n;
			break;
		}
		else
		{
			n = 2*n;
		}
	}
	return k;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

