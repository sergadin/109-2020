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
	int n = 1;
	do
	{
		S += summand;
		n += 2;
		summand *= -x * x / (n * (n - 1));
	} while ((n < 1000) || (Abs(summand) < eps));

	if (Abs(summand) >= eps)
	{
		*Error = 1;
		return 0.0;
	}
	
	*Error = 0;
	return S;
}