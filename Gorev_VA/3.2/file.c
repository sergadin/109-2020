#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "min_value.h"

double F1(double x);
double F1(double x)
{
	return x * x * x - x;
}

double F2(double x);
double F2(double x)
{
	return sin(x);
}

double F3(double x);
double F3(double x)
{
	return x + 1.5;
}

int main(void)
{
	int* Error;
	double V;
	Error = (int*)malloc(1 * sizeof(int));

	printf("f(x) = x^3 - x at [0, 2]\n");
	V = min_value(F1, 0.0, 2.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, -0.3849001795);

	printf("f(x) = sin(x) at [3, 6]\n");
	V = min_value(F2, 3.0, 6.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, -1.0);

	printf("f(x) = x^3 - x at [0, 1]\n");
	V = min_value(F3, 0.0, 2.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, 1.5);
	return 0;
}
