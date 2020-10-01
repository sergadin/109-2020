#include <stdio.h>
#include <math.h>
#include "prog5-3.h"

double ParabolaInterpol(double x, double *xarray, int n, fpointer f)
{
	double yarray[n];
	double a,b,c, approx_value;
	int central, i;

	for (i=0; i<n; ++i)
	{
		yarray[i] = f(xarray[i]);
	}
	
	for(i=0;i<n;i++) 
	{
		if (xarray[i]> x) break;
		central=i;
	}
	if (central==0) n++;
	
	a=(yarray[central+1]-yarray[central-1])/((xarray[central+1]-xarray[central-1])*(xarray[central+1]-xarray[central])) - (yarray[central]-yarray[central-1])/((xarray[central]-xarray[central-1])*(xarray[central+1]- xarray[central]));
	
	b=(yarray[central]-yarray[central-1])/(xarray[central]-xarray[central-1]) - a*(xarray[central]+xarray[central-1]);
	
	c= yarray[central-1] - b*xarray[central-1]-a*xarray[central-1]*xarray[central-1];
	
	approx_value = a*x*x+b*x+c;
	
	return approx_value;
}

