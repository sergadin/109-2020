#include <math.h>
#include <stdio.h>
#include "z5_3.h"

double func (double * a, double * b, double x, double eps, int n)
{
	int i;
	int i1=-2;
	int i2=-2;

	double a0, a1, a2;//парабола

	for (i=1; i<n; i++)
	{
		if ((x > a[i-1]) && ( x < a[i+1]))
		{
			i1 = i - 1;
			i2 = i;
		}
	}
	//нашли отрезок, где лежит х

	if (i2 == n - 1)
	{
		i1 = i1 - 1;
	}
//	else
//	{
//
//	}
	//нашли 3 точки, чтобы по ним построить параболу

	a2 = (b[i1+2] - b[i1])/(a[i1+2] - a[i1])/(a[i1+2] - a[i1+1]) - (b[i1+1] - b[i1])/(a[i1+1] - a[i1])/(a[i1+2] - a[i1+1]);
	a1 = (b[i1+1] - b[i1])/(a[i1+1] - a[i1]) - a2*(a[i1+1] + a[i1]);
	a0 = b[i1] - a1*a[i1] - a2*a[i1]*a[i1];

	x = x*x*a2 + x*a1 + a0;
	return x;

}













