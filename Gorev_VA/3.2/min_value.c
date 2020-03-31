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
			q = 1; // íŕ ńëĺäóţůĺě řŕăĺ íóćíî ń÷čňŕňü ő1
		}
		else
		{
			b = x1;
			x1 = x0;
			q = 0; // íŕ ńëĺäóţůĺě řŕăĺ íóćíî ń÷čňŕňü ő0
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
		x2 = x0;
		x0 = a;
		x1 = b;
		f0 = (*f)(x0);
		f1 = (*f)(x1);
		f2 = (*f)(x2);
		x2 = x2 - ((x2 - x1) * (x2 - x1) * (f2 - f0) - (x2 - x0) * (x2 - x0) * (f2 - f1)) / ((x2 - x1) * (f2 - f0) - (x2 - x0) * (f2 - f1)) * 0.5;
		if ((x2 >= a) && (x2 <= b))
		{
			*Error = 0;
			return f(x2);
		}
		else
		{
			*Error = 1;
			return 0.0;
		}

	}
}