#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integral.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a), (b)), (c)))
#define E 0.00000001

double zero(double x);
double linear(double x);
double square(double x);
double sin_x(double x);
double e_x(double x);
double error_func(double x);
 
int main(void) 
{
	ErrorCode ec;
	int i = 0, num = 6;
	double X_a = -7, X_b = 1, result, eps = 0.01;
	RRF funcs[] = {zero, linear, square, sin_x, e_x, error_func};
	double true_answer[] = {0, -24, 114.666666667, 0.213599948, 2.717369946, 0};

	for(i = 0; i < num; i++) 
	{
		result = integral(funcs[i], X_a, X_b, E, &ec);
		if (ec != SF_OK || fabs(result) > fabs(X_a-X_b)*1000000 || isnan(result) != 0)
                {
                        printf("ERROR test %d\n", i + 1);
                }
		else
		{
			printf("TEST %d true: %lf real: %lf\n", i + 1, true_answer[i], result);
			if (fabs(result-true_answer[i]) > eps*MAX(1, fabs(result), fabs(true_answer[i]))) 
			{
				printf("incorrect TEST %d\n", i+1);
			}
		}
	}

	return 0;
}

double zero(double x) 
{
	return x*0;
}

double linear(double x) 
{
	return x;
}

double square(double x) 
{
	return x*x;
}

double sin_x(double x) 
{
	return sin(x);
}

double e_x(double x) 
{
	return exp(x);
}
 
double error_func(double x)
{
	return sin(1/x)*exp(1/x);
}
