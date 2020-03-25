#include <stdio.h>

#define eps 0.000001;

double one(double x);
double one(double x)
{
	return 1 + 0*x;
}

double derivative(double (*f)(double x), double x);
double derivative(double (*f)(double x), double x)
{
	return (f(x + eps) - f(x)) / eps;
}

double func(double (*f)(double));
double func(double (*f)(double))
{
	return 2 * (*f)(1);
}

double SQR(double x);
double SQR(double x)
{
	return x*x;
}

int main(void)
{
	printf("%f", derivative(SQR, 2));
	return 0;
}