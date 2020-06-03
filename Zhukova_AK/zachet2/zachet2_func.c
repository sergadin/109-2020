#include <stdio.h>
#include "zachet2.h"


void func (int n, int m, double * a)
{
	int i, j, j1;
	int imin = 0;
	int jmin = m;
	double s = 0;
	double a_max;

	for (i=0;i<n; i++)
	{
		s = 0;
		for (j=0;j<m; j++)
		{
			s = s + a[i*m+j];
		}
		s = s/m;
//		i1 = i;
		j1 = 0;
		a_max = a[i*m + 0];
		for (j=0;j<m; j++)
		{
			if (a[i*m+j]>a_max)
			{
				a_max = a[i*m+j];
				j1 = j;
			}
		}

		for (j=0;j<m; j++)
		{
			if ((a[i*m+j] > s) && (a[i*m+j] <a_max))
			{
				j1 = j;
				a_max = a[i*m+j];
			}
		}

		if (jmin>j1)
		{
			jmin = j1;
			imin = i;
		}

	}

//printf ("imin=%d\n", imin);
	for (i=0;i<n; i++)
	{
		for (j=0;j<m; j++)
		{
			a[i*m+j] = (a[i*m+j] + a[imin*m+j])/2;
		}

	}
}
