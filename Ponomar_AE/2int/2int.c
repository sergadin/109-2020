#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "2int.h"

#define max(a, b) (((a) > (b))?(a):(b))
#define MAX(a, b, c) max(a, max(b, c))

static double INTEGRAL(double X_a, double X_b, double n, RRFUN func);

double dcsn_f_x(double X_1, double X_2, double E, RRFUN1 func, ErrorCode *error_code)
{
	double left = X_1, mid = (X_1+X_2)/2, right = X_2, f_left, f_mid, f_right, cur_length = X_2-X_1;

	if (((*func)(left)) * ((*func)(right)) >= 0)
	{
		*error_code = SF_ERROR;
		return 0;
	}

	while(cur_length > E)
	{
		mid = (left+right)/2;
		f_mid = (*func)(mid);
		f_left = (*func)(left);
		f_right = (*func)(right);

		if(f_mid*f_right <= 0)
		{
			left = mid;
			f_left = f_mid;
		}
		else
		{
			right = mid;
			f_right = f_mid;
		}
		cur_length = right-left;
	}

	return (left+right)/2;
}


static double INTEGRAL(double X_a, double X_b, double n, RRFUN func)
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

double integral(double X_a, double X_b, double E, RRFUN func)
{
	int i, n = 1000;
	double int1 = INTEGRAL(X_a, X_b, n, func), int2 = INTEGRAL(X_a, X_b, n, func);
	
	while((fabs(int1 - int2)/3 > E * MAX(1, int1, int2)) && (n <= 100000000))
	{
			n = n * 2;
			int1 = INTEGRAL(X_a, X_b, n, func);
			int2 = INTEGRAL(X_a, X_b, n * 2, func);
	}

	return int2;
}


