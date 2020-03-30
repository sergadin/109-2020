#include <stdio.h>

#define eps 0.000001

double derivative(double (*f)(double), double x);
double derivative(double (*f)(double), double x)
{
	return ((*f)(x + eps / 2.0) - (*f)(x)) / (eps / 2.0);
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
	if ((b - a) < (eps))
		return c;
	while (1)
	{
		//printf("%f\n", derivative(f, b));
		c = b - (*f)(b) / derivative(f, b);
		//printf("b %f\n", c);
		if ((c > b) || (c < a))
		{
			c = a - (*f)(a) / derivative(f, a);
			//printf("a %f\n", c);
			if (((b - a) < (eps)) || ((c - a) < (eps)))
				break;
			else
				a = c;
		}
		else
			if (((b - a) < (eps)) || ((b - c) < (eps)))
				break;
			else
				b = c;
	}
	return c;
}

double one(double x);
double one(double x)
{
	return 1.0 + 0.0*x;
}

double func(double (*f)(double));
double func(double (*f)(double))
{
	return 2.0 * (*f)(1.0);
}

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

int main(void)
{
	printf("%f\n", root(F1, 0.0, 2.0));
	printf("%f\n", root(F2, -6.0, -2.0));
	printf("%f\n", root(F3, 0.5, 2.0));
	return 0;
}
