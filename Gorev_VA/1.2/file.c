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
	if ((b - a) < (eps / 2))
		return c;
	while (1)
	{
		c = b - (*f)(b) / derivative(f, b);
		if ((c > b) || (c < a))
		{
			c = a - (*f)(a) / derivative(f, a);
			if (((b - a) < (eps / 2)) || ((c - a) < (eps / 2)))
				break;
			else
				a = c;
		}
		else
			if (((b - a) < (eps / 2)) || ((b - c) < (eps / 2)))
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

double F1(double x);
double F1(double x)
{
	return x*x - 1;
}

double F2(double x);
double F2(double x)
{
	return 1/256 * x*x*x*x + 4;
}

double F3(double x);
double F3(double x)
{
	return 1/(x*x) - 2;
}

int main(void)
{
	printf("%f\n", root(F1, 0, 2));
	printf("%f\n", root(F2, -6, -2));
	printf("%f\n", root(F3, 1 / 2, 2));
	return 0;
}
