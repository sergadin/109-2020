#include <stdio.h>

#define eps 0.000001

double derivative(double (*f)(double), double x);
double derivative(double (*f)(double), double x)
{
	return ((*f)(x + eps / 100) - (*f)(x)) / (eps / 100);
}

double root(double (*f)(double), double a, double b);
double root(double (*f)(double), double a, double b)
{
	double c;
	if (a > b)
	{
		c = a;
		a = b;
		b = c;
	}
	c = a;
	if ((b - a) < eps)
		return c;
	printf("%f\n", c);
	while (1)
	{
		c = b - (*f)(b) / derivative(f, b);
		printf("%f\n", c);
		if (((b - a) < eps) || (b - c) < eps)
			break;
		else
			b = c;
	}
	return c;
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
	return x*x - 1;
}



int main(void)
{
	printf("%f\n", root(SQR, 0, 2));
	return 0;
}