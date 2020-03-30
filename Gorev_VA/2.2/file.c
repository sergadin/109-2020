#include <stdio.h>

double trap_sum(double (*f) (double), double a, double b, int N);
double trap_sum(double (*f) (double), double a, double b, int N)
{
	double S = 0, x1, x2;
	x1 = a;
	for (int i = 1; i <= (N + 1); i++)
	{
		x2 = (a * ((double)(N - i) / (double)N) + b * ((double)i / (double)N));
		S += 0.5 * (f(x2) + f(x1)) / (double)N;
		x1 = x2;
	}
	if (a > b)
		S = -S;
	return S;
}

double X(double x)
{
	return x;
}

int main(void)
{
	int N = 100;
	printf("%f\n", trap_sum(X, 0, 1, N));
	return 0;
}
