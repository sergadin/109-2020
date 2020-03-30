#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integral.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a), (b)), (c)))
#define E 0.0000001

double zero(double x);
double linear(double x);
double square(double x);
double sin_x(double x);
double e_x(double x);

int main(void) 
{
	int i = 0, num = 5;
	double X_a = -7, X_b = 1, result;
	RRF funcs[] = {zero, linear, square, sin_x, e_x};

	double true_answer[] = {0, -24, 114, 0.213599948, 2.717369946};

	for(i = 0; i < num; i++) 
	{
		result = integral(funcs[i], X_a, X_b, E);
		printf("TEST %d true: %lf real: %lf \n", i + 1, true_answer[i], result);
		if (fabs(result-true_answer[i]) > E*MAX(1, 100/E * fabs(result), 100/E * fabs(true_answer[i]))) 
		{
			printf("ERROR test %d\n", i + 1); 
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

