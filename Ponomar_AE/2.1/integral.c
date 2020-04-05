#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "integral.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a),(b)), (c)))

static double INTEGRAL(RRF func, double X_a, double X_b, double n);

static double INTEGRAL(RRF func, double X_a, double X_b, double n)
{
	double x, dx = (X_b - X_a)/n;
	double result = 0;
	
	for(int i = 1; i < n; i++)
	{
		x = X_a + dx * (i + 0.5);
		result += (*func)(x)*dx;
	}
	
	return result;
}

double integral(RRF func, double X_a, double X_b, double E, ErrorCode *error_code)
{
	int i, n = 1000;
	double int1 = INTEGRAL(func, X_a, X_b, n), int2 = INTEGRAL(func, X_a, X_b, n);
	*error_code = INT_OK;

	while((fabs(int1 - int2)/3 > E * MAX(1, int1, int2)) && (n <= 100000000))
	{
			n = n * 2;
			int1 = INTEGRAL(func, X_a, X_b, n);
			int2 = INTEGRAL(func, X_a, X_b, n * 2);
	}

	if(n > 100000000)
	{
		*error_code = INT_ERROR;
	}

	return int2;
}
