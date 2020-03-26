#include<math.h>
#include<stdio.h>
#include"interpol.h"





double interpol(double x[], double y[], int n, double x0, RRF func)
{
	double y0 = -1;
	double p = 1;
	for(int i = 0; i < n; i++)
	{
		y0 += p;
		p = 1;
		for(int j = 0; j < n; j++)
		{
			if(j != i)
				p = p*(x0 - x[j])/(x[i] - x[j]);

		}
		p = p*y[i];

	}
	return y0;
}
