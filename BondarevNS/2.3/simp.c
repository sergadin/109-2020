#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simp.h"
static double simp(double a, double b, double eps, RRFUN ffunc);

static double simp(double a, double b, double n, RRFUN ffunc)
{
	int i;
	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0, int1 = 0, int2 = 0, k = 1;
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
	res = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));
	return res;
}

double integ(double a, double b, double eps, RRFUN ffunc)
{
	int n = 2;
	double int1 = simp(a, b, n, ffunc), int2 = simp(a, b, 2*n, ffunc);
	while ((n > 0) && (fabs(int2 - int1) > eps) && (n < 67108864))
	{                                              
		int1 = simp(a, b, n, ffunc);
		n = 2*n;
		int2 = simp(a, b, n, ffunc);
	}
	return int2;
}

