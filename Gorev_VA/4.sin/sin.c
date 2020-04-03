#include "sin.h"

double Abs(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

double Sin(double x, double eps, int* Error)
{
	double S = 0, summand = x;
	for (int n = 1; n < 1000; n += 2, summand *= x * x / (n * (n - 1)))
	{
		S += summand;
		n += 2, summand *= x * x / (n * (n - 1));
		S -= summand;

		if (Abs(summand) < eps)
			break;
	}

	if (Abs(summand) >= eps)
	{
		*Error = 1;
		return 0.0;
	}
	
	*Error = 0;
	return S;
}