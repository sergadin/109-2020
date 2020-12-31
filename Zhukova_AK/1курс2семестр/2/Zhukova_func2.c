#include <stdio.h>
#include "Zhukova_func2.h"

double func (double( * funcs[]) (double), int n, double x)
{
	int i;

	for (i=0; i<n; i++)
	{
		x =(* funcs [n-i-1]) (x);
	}

	return x;
}
