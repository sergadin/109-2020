#include "trap_sum.h"

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
