i#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "integral.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a),(b)), (c)))

static double INTEGRAL(RRF func, double X_a, double X_b, double E);

static double INTEGRAL(RRF func, double X_a, double X_b, double E)
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

double integral(RRF func, double X_a, double X_b, double E, ErrorCode *error_code)
{
	int i;
	double	eps = 0.00001;
	double int1 = INTEGRAL(func, X_a, X_b, eps), int2 = INTEGRAL(func, X_a, X_b, eps);
	*error_code = INT_OK;
	while((fabs(int1 - int2) > E * MAX(1, int1, int2)) && (eps >= 0.0000000001))
	{
			eps = eps/2;
			printf("%lf", eps);
			int1 = INTEGRAL(func, X_a, X_b, eps);
			int2 = INTEGRAL(func, X_a, X_b, eps/2);
	}

	if(eps <= 0.0000000001)
	{
		*error_code = INT_ERROR;
	}
	return int2;
}
