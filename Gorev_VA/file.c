#include <stdio.h>

#define eps 0.000001

double derivative(double (*f)(double), double x);
double derivative(double (*f)(double), double x)
{
	return (f(x + eps) - f(x)) / eps;
}

double root(double (*f)(double), double a, double b);
double root(double (*f)(double), double a, double b)
{
	if (a > b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
	return 0*(*f)(1);
}

double one(double x);
double one(double x)
{
	return 1 + 0*x;
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
	double a = 4, b = 1;
	a = a + b;
	b = a - b;
	a = a - b;
	printf("%f %f\n", a, b);
	printf("%f\n", derivative(SQR, 2));
	return 0;
}