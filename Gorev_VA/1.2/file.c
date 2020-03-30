#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "root.h"

double F1(double x);
double F1(double x)
{
	return x*x - 1.0;
}

double F2(double x);
double F2(double x)
{
	return 1.0/256.0 * x*x*x*x - 4.0;
}

double F3(double x);
double F3(double x)
{
	return 1.0/(x*x*x) - 2.0;
}

double F4(double x);
double F4(double x)
{
	return x*x*x*x - x*x;
}

double Arctg(double x);
double Arctg(double x)
{
	return atan(x);
}

int main(void)
{
	int* Error;
	double R;
	Error = (int*)malloc(1 * sizeof(int));
	
	*Error = 0;
	R = root(F1, 0.0, 2.0, Error);
	printf("f(x) = x^2 - 1 at [0, 2]\n");
	if (*Error)
		printf(" Error\n");
	else
		printf(" calculated root: %f\n actual root:     %f\n", R , 1.0);
	
	R = root(F2, -2.0, -6.0, Error);
	printf("f(x) = 1/256 x^4 - 4 at [-2, -6]\n");
	if (*Error)
		printf(" Error\n");
	else
		printf(" calculated root: %f\n actual root:     %f\n", R, -5.6568542495);
	
	R = root(F3, 0.5, 2.0, Error);
	printf("f(x) = 1/x^3 - 2 at [0.5, 2]\n");
	if (*Error)
		printf(" Error\n");
	else
		printf(" calculated root: %f\n actual root:     %f\n", R, 0.7937005293);
	
	R = root(F4, -0.75, 0.75, Error);
	printf("f(x) = x^4 - x^2 at [-0.75, 0.75]\n");
	if (*Error)
		printf(" Error\n");
	else
		printf(" calculated root: %f\n actual root:     %f\n", R, 0.0);
	
	R = root(Arctg, -0.75, 0.75, Error);
	printf("f(x) = arctg(x) at [-5, 5]\n");
	if (*Error)
		printf(" Error\n");
	else
		printf(" calculated root: %f\n actual root:     %f\n", R, 0.0);
	
	return 0;
}
