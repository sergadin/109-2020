#include <math.h>
#include "min_value.h"

double min_value(double(*f) (double), double a, double b, int* Error)
{
	double x0, x1, x2, f0, f1, f2;
	int q;
	if (a > b)
	{
		x1 = a;
		a = b;
		b = x1;
	}
	x0 = b - (b - a) * (sqrt(5) - 1) * 0.5;
	q = 1;
	for (int i = 1; i <= 1000; i++)
	{
		if (q)
			x1 = a + (b - a) * (sqrt(5) - 1) * 0.5;
		else
			x0 = b - (b - a) * (sqrt(5) - 1) * 0.5;

		if ((*f)(x0) >= (*f)(x1))
		{
			a = x0;
			x0 = x1;
			q = 1; // на следующем шаге нужно считать х1
		}
		else
		{
			b = x1;
			x1 = x0;
			q = 0; // на следующем шаге нужно считать х0
		}
		if ((b - a) < eps)
			break;
	}
}
