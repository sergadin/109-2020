#include <stdio.h>
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
	double S = 0, summand = Abs(x);
	
	for (int n = 1; n < 1000; n++, summand *= Abs(x) / n)
	{
		if (summand < eps)
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
	summand = Abs(x);
	printf("   %d\n", N);
	for (int n = 1; n < N; n += 2, summand *= Abs(x) * Abs(x) / (n * (n - 1)))
	{
		if ((n % 4) == 1)
			S += summand;
		else
			S -= summand;
		prinf("   %f\n", S);
	}
	return S;
}
