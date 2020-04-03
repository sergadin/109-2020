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

double F4(double x);
double F4(double x)
{
	return -x * x * 2.0;
}

double F5(double x);
double F5(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

double F6(double x);
double F6(double x)
{
	return cos(1 / x)*exp(1 / (x + 100));
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

	printf("f(x) = x + 1.5 at [0, 1]\n");
	V = min_value(F3, 0.0, 1.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, 1.5);

	printf("f(x) = -2x^2 at [-1, 1]\n");
	V = min_value(F4, -1.0, 1.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, -0.0);

	printf("f(x) = |x| at [-1, 1]\n");
	V = min_value(F5, -1.0, 1.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, 0.0);
	
	// тест взят у кирилла зуева, который сдал эту же самую программу
	// отличий в алгоритме я не нашел
	printf("f(x) = cos(1 / x)*exp(1 / (x + 100)); at [0, 4]\n");
	V = min_value(F6, 0.0, 4.0, Error);
	if (*Error)
		printf("Error\n");
	else
		printf(" calculated min value: %f\n actual min value:     %f\n", V, -1.0100181188);

	return 0;
}
