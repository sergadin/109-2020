#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "integral.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a), (b)), (c)))

double integral(RRF func, double X_a, double X_b, double E, ErrorCode *error_code)
{
	int n = 2;
	double result1 = 0, result2 = 0, x, dx = (X_b - X_a)/n;
	
	for (int i = 0; i < n; i++) 
	{
		x = X_a + (i * 0.5) * dx;
		result2 += func(x) * dx;
	}
	n = n * 2;

	while ((fabs(result1-result2))/3 >= (E*MAX(1, result1, result2)))
	{
		result1 = result2;
		result2 = 0;
		dx = (X_b - X_a)/n;

		for (int i = 0; i < n; i++) 
		{
			x = X_a + (i + 0/5) * dx;
			result2 += func(x) * dx;
		}

		n = n * 2;
	}

	return result2;
}

