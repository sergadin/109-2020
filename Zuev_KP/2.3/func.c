#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"func.h"

double simp(double a, double b, double n, RRFUN ffunc, RRFUN fsum)


{
     	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0;
	if (n == 0)
	{
	return 0;
	}
	h = (b-a)/(2*n);
	for(int i = 1; i < n-1; i++)
	{
		x = a+2*i*h;
		res1 = (*fsum)(res, (*ffunc)(x, 1));
	}
	for(int i = 1; i < n; i++)
	{
		x = a+(2*i-1)*h;
		res2 = (*fsum)(res, (*ffunc)(x, 1));
	}
	res = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a, 1) + (*ffunc)(b, 1));
	return res;
}




