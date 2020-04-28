#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "trap_sum.h"

double X(double x);
double X(double x)
{
	return x;
}

double SQR(double x);
double SQR(double x)
{
	return x*x;
}

double F1(double x);
double F1(double x)
{
	return x*x*x*x*x*x - x*x*x*x - 2 * x + 1;
}

double F2(double x);
double F2(double x)
{
	return x * sin(x);
}

double F3(double x);
double F3(double x)
{
	if (x < (eps / 100))
		return 0.0;
	return sin(1 / x);
}

int main(void)
{
	int* Error;
	double I;
	Error = (int*)malloc(1 * sizeof(int));
	*Error = 0;
	printf("Integrating with trapeziodal rule...\n");
	
	printf("f(x) = x at [0, 1]\n");
	printf(" N = 100:   %f\n N = 1000:  %f\n N = 10000: %f\n", trap_sum(X, 0, 1, 100), trap_sum(X, 0, 1, 1000), trap_sum(X, 0, 1, 10000));
	I = integral(X, 0.0, 1.0, Error);
	if (*Error)
		printf("Error: the integral could not be calculated\n");
	else
		printf(" calc int:  %f\n", I);
	printf(" actual:    %f\n", 0.5);

	printf("f(x) = x^2 at [2, -1]\n");
	printf(" N = 100:   %f\n N = 1000:  %f\n N = 10000: %f\n", trap_sum(SQR, 2, -1, 100), trap_sum(SQR, 2, -1, 1000), trap_sum(SQR, 2, -1, 10000));
	I = integral(SQR, 2.0, -1.0, Error);
	if (*Error)
		printf("Error: the integral could not be calculated\n");
	else
		printf(" calc int:  %f\n", I);
	printf(" actual:    %f\n", -3.0);

	printf("f(x) = x^6 - x^4 - 2x + 1 at [0, 2]\n");
	printf(" N = 100:   %f\n N = 1000:  %f\n N = 10000: %f\n", trap_sum(F1, 0, 2, 100), trap_sum(F1, 0, 2, 1000), trap_sum(F1, 0, 2, 10000));
	I = integral(F1, 0, 2.0, Error);
	if (*Error)
		printf("Error: the integral could not be calculated\n");
	else
		printf(" calc int:  %f\n", I);
	printf(" actual:    %f\n", 9.8857142857);

	printf("f(x) = x sin(x) at [0, 2pi]\n");
	printf(" N = 100:   %f\n N = 1000:  %f\n N = 10000: %f\n", trap_sum(F2, 0, 2*pi, 100), trap_sum(F2, 0, 2*pi, 1000), trap_sum(F2, 0, 2*pi, 10000));
	I = integral(F2, 0, 2 * pi, Error);
	if (*Error)
		printf("Error: the integral could not be calculated\n");
	else
		printf(" calc int:  %f\n", I);
	printf(" actual:    -2pi\n");
	
	printf("f(x) = sin(1/x) at [0, 1/pi]\n");
	printf(" N = 100:   %f\n N = 1000:  %f\n N = 10000: %f\n", trap_sum(F3, 0, 1 / pi, 100), trap_sum(F3, 0, 1 / pi, 1000), trap_sum(F3, 0, 1 / pi, 10000));
	I = integral(F3, 0, 1 / pi, Error);
	if (*Error)
		printf("Error: the integral could not be calculated\n");
	else
		printf(" calc int:  %f\n", I);
	printf(" actual:    -0.0736679\n");

	return 0;
}
