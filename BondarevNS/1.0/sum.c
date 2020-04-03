#include <stdio.h>
#include "sum.h"
double sum(RRFUN function, double *array, int n)
{
	int i;
	double sum = 0;
	for ( i = 0; i < n; i++)
	{
		sum += (*function)(array[i]);
	}
	return sum;
}
