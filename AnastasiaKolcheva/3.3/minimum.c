#include <math.h>
#include "minimum.h"

double findMinimum(func f, double a, double b, double epsilon)
{
	epsilon = 0.000001;
	double h = 0.1;
	int index, minimalnterv;
	double minimalVertex, minimalValue;
	double A, B, C;
	

	while (fabs(b - a) > epsilon)
	{
		minimalValue = f(a);
		minimalnterv = 0;

		for (index = 1; index <= 1/h; ++index)
		{
			double newMinimal = f(a + index * h * (b - a));

			if (newMinimal < minimalValue)
			{
				minimalValue = newMinimal;
				minimalnterv = index;
			}
		}

		if (minimalnterv == 0)
		{
			a = a;
			b = a + h * (b - a);
		}
		else if (minimalnterv == 1/h)
		{
			b = b;
			a = b - h * (b - a);
		}
		else
		{
			a = a + (minimalnterv - 1.0) * h * (b - a);
			b = a + (minimalnterv + 1.0) * h * (b - a);
		}
	} 

	double c = (a + b) / 2;
	A = (f(c) - (c * (f(b) - f(a)) + b * f(a) - a * f(b)) / (b - a)) / (c * (c - a - b) + a * b);
	B = (f(b) - f(a)) / (b - a) - A * (a + b);
	C = (b * f(a) - a * f(b)) / (b - a) + A * a * b;
	minimalVertex = - B / (2 * A);


	if (minimalVertex < a || minimalVertex > b)
	{
		if (f(a) > f(b))
		{
			return f(b);
		}
			
		else
		{
			return f(a);
		}
	}
	return f(minimalVertex);
}