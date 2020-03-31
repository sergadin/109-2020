#include <stdio.h>
#include <math.h>

#define eps 0.0000001

double Min(double(*f) (double), double a, double b, int* Error);
double Min(double(*f) (double), double a, double b, int* Error);
{
	double x0, x1, x3, f1, f2, f3;
	int q;
	if (a > b)
	{
		x1 = a;
		a = b;
		b = x1;
	}
	x0 = b - (b - a) * (sqrt(5) - 1) * 0.5;
	q = 1;

	for (int i = 1; i <= 1000000; i++)
	{
		if (q)
			x1 = a + (b - a) * (sqrt(5) - 1) * 0.5;
		else
			x0 = b - (b - a) * (sqrt(5) - 1) * 0.5;

		if ((*f)(x0) >= (*f)(x1))
		{
			a = x0;
			q = 1; // на следующем шаге нужно считать х1
		}
		else
		{
			b = x1;
			q = 0; // на следующем шаге нужно считать х0
		}

		if ((b - a) < eps)
			break;
	}

	if ((b - a) >= eps)
	{
		*Error = 1;
		return 0.0;
	}
	else
	{
		*Error = 0;
		x1 = a;
		x2 = 0.5 * (a + b);
		x3 = b;
		f1 = f(x1);
		f2 = f(x2);
		f3 = f(x3);
		return -0.5 * (x2 * x2 * f3 - x3 * x3 * f2 + x3 * x3* f1 - x1 * x1 * f3 + x1 * x1 * f2 - x2 * x2 * f1) / (f2 * x3 - f3 * x2 + f3 * x1 - f1 * x3 + f1 * x2 - f2 * x1);
	}
}

double F1(double x);
{
	return x * x * x - x;
}

int main(void)
{
	int* Error;
	printf("%f", Min(F1, 0, 2, Error));
	return 0;
}