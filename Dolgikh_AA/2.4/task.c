#include <stddef.h>
#include "task.h"
#include <math.h>

double piece(RRFUN f, double a, double b)
{
	return (f(0.788675 * a + 0.211325 * b) + f(0.211325 * a + 0.788675 * b)) * (b - a) / 2;
}
double gauss(RRFUN f, double a, double b, int N)
{
	int i;
	double I = 0;
	for(i = 1; i < N; i++)
		I += piece(f, a + (i-1)*(b-a)/N, a + i*(b-a)/N);
	return I;
}
double integrate(RRFUN f, double a, double b, double eps, ErrorCode *perr)
{
	int i;
	int N = 4;
	double In = 0, I2n = 0;
	
	if(perr != NULL)
		*perr = INT_NOTOK;

	In = gauss(f, a, b, N);
	I2n = gauss(f, a, b, 2*N);
	while((!(fabs(I2n - In)*2 < eps))&&(N < 1073741824))
	{
		In = gauss(f, a, b, N);
		N = 2*N;
		I2n = gauss(f, a, b, N);
	}
	if(fabs(I2n-In)*2 < eps)
		*perr = INT_OK;
	return I2n;
}
