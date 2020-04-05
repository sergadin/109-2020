#include <stdio.h>
#include <stddef.h>
#include "integration.h"
#include <math.h>

double part_sum(dndFUNC f, double a, double b)
{
	return (f(0.788675 * a + 0.211325 * b) + f(0.211325 * a + 0.788675 * b)) * (b - a) / 2;
}
double gaus(dndFUNC f, double a, double b, int N)
{
	int i;
	double I = 0;
	for(i = 1; i < N; i++)
		I += part_sum(f, a + (i-1)*(b-a)/N, a + i*(b-a)/N);
	return I;
}
int integrate(dndFUNC f, double a, double b, double eps, double *x)
{
	int N = 4;
	double In = 0, I2n = 0;
    
	In = gaus(f, a, b, N);
	I2n = gaus(f, a, b, 2*N);
	while((!(fabs(I2n - In)*2 < eps))&&(N < 1073741824))
	{
        printf("%d\n", N);
		In = gaus(f, a, b, N);
		N = 2*N;
		I2n = gaus(f, a, b, N);
	}
	*x = I2n;
	return N;
}
