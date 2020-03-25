#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simpson.h"

double simp(double a, double b, double ep, RRFUN ffunc)


{
	int n = 4, n1 = 0, n2 = 0, i;
	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0, i1 = 0, i2 = 0;
	while (n > 0)
	{
		n1 = n;
		h = (b-a)/(2*n1);
		for(i = 1; i < n1-1; i++)
		{
			x = a+2*i*h;
			res1 = res1 + (*ffunc)(x);
		}
		for(i = 1; i < n1; i++)
		{
			x = a+(2*i-1)*h;
			res2 = res1 + (*ffunc)(x);
		}
		i1 = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));

		//printf("%lf\n", i1);

		n2 = n*2;
		h = (b-a)/(2*n2);
		for(i = 1; i < n2-1; i++)
		{
			x = a+2*i*h;
			res1 = res1 + (*ffunc)(x);
		}
		for(i = 1; i < n2; i++)
		{
			x = a+(2*i-1)*h;
			res2 = res1 + (*ffunc)(x);
		}
		i2 = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));

		//printf("%lf\n", i2);

		if (modul(i2 - i1) <= ep)
		{
			res = i2;
			break;	
		}
		else
		{
			n = n2;
			printf("%d\n", n);
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

