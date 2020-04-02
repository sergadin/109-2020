#include "task.h"
#include <math.h>

double littlesegmentintegration(RRFUN f, double a, double b)
{
	return (f(0.788675 * a + 0.211325 * b) + f(0.211325 * a + 0.788675 * b)) * (b - a) / 2;
}
double gaussintegration(RRFUN f, double a, double b, int N)
{
	double I = 0;
	int k;
	for(k = 1; k <= N; k++)
		I += littlesegmentintegration(f, a + (k - 1) * (b - a) / N, a + k * (b - a) / N);
	return I;
}
