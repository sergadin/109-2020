#include <stdio.h>
#include <math.h>
#include "task.h"
#define eps 1e-6

double square(double x);

int main(void)
{
	RRFUN f;
	double a, b;
	fprintf(stdout, "Enter a ");
	fscanf(stdin, "%lf",&a);
	f = square;
	fprintf(stdout, "Derivative of x2 in a equal %lf\n", deriv(f, a, eps));	
	fprintf(stdout, "2nd derivative of x2 in a equal %lf\n", secderiv(f, a, eps));
	fprintf(stdout, "Enter a and b ");
	fscanf(stdin, "%lf %lf", &a, &b);
	fprintf(stdout, "Root is %lf\n", newton(f, a, b, eps));
	return 0;	
}

double square(double x)
{
	return x * x - 2;
}
