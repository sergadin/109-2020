#include <stdio.h>
#include <math.h>
#include "minimum.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a), (b)), (c)))
#define E 0.0000000001

double func1(double x);
double func2(double x);
double func3(double x);

int main(void)
{
	int i, N = 3;
	RRFUN funcs[] = {func1, func2, func3};
	double result, true_answer[] = {-5, -6, -12.1716124};
	double xa = -5, xb = 4, eps = 0.000001;
	for(i = 0; i < N; i++)
	{
		result = minimum(xa, xb, E, funcs[i]);
		printf("true: %lf real: %lf+-%lf\n", true_answer[i], result, eps);
		if (fabs(result - true_answer[i]) > eps * MAX(1, result, true_answer[i]))
		{
		       	printf("ERROR test %d\n", i+1);		
		}
	}
}

double func1(double x)
{
	return x;
}

double func2(double x)
{
	return x + (0.2*x)*(0.2*x)*(0.2*x);
}

double func3(double x)
{
	return (x+2)*(x+2)*(x+2) - 10*x -20;
}
