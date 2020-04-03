#include "sin.h"

double Abs(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

double Sin(double x, double eps, int* Error)
{
	int N = 0;
	double S = 0, summand = x;
	for (int n = 1; n < 1000; n += 2, summand *= x * x / (n * (n - 1)))
	{
		if ((n % 4) == 1)
			S += summand;
		else
			S -= summand;

		if (Abs(summand) < eps)
		{
			N = n;
			break;
		}
	}

	if (N == 0)
	{
		*Error = 1;
		return 0.0;
	}
	
	*Error = 0;
	return S;
}