#include "trap_sum.h"

#define eps 0.000001

double trap_sum(double (*f) (double), double a, double b, int N)
{
	double S = 0, x1, x2;
	x1 = a;
	for (int i = 1; i <= N; i++)
	{
		x2 = a * (N - i) / N + b * i / N;
		S += 0.5 * (f(x2) + f(x1)) * (b - a) / N;
		x1 = x2;
	}
	return S;
}

double interal(double (*f) (double), double a, double b, int* Error)
{
	double I = 0, I1 = 0;
	int N = 100;
	for (int i = 2; i <= 10; i++, N *= 10, I1 = I)
	{
		I = trap_sum(f, a, b, N);
		if (((I - I1) < eps) && ((I1 - I) < eps))
		{
			*Error = 0;
			return I;
		}
	}
	*Error = 1;
	return I;
}
