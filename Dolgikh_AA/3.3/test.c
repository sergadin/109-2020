#include <stdio.h>
#include "task.h"
#include "math.h"
#define eps 0.000001
#define E 2.718281828

double sqr(double x);
double cube(double x);
double exp(double x);

int main(void)
{
	RRFUN F[5] = {sin, sin, sqr, cube, exp};
	double A[5] = {3, 1, -1, 2, 0};
	double B[5] = {6, 3, 2, 3, 2};
	double trueans[5] = {-1, 0.14112, 0, 8, 1};
	int i;
	double res;

	for(i = 0; i < 5; i++)
	{
		fprintf(stdout, "Test #%d ",i+1);
		res = minimum(F[i], A[i], B[i], eps);
		fprintf(stdout, "Answer: %lf Correct answer: %lf\n", res, trueans[i]);
	}
	
	return 0;
}

double sqr(double x)
{
	return x * x;
}
double cube(double x)
{
	return x * x * x;
}
double exp(double x)
{
	return pow(E, x);
}
