#include <stdio.h>

#include "f.h"
double f1 (double x)
{
	return x*x + 5*x - 6;
}

int main(void)
{
	double a = -4, b = 2, eps = 0.0001, m;
	if(f1(a)*f1(b) >= 0)
	{
		printf("FAULT");
	}
	if(f1(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	m = root(f1, a, b, eps);
	printf("Answer = %e\n", m);
	return 0;
}


