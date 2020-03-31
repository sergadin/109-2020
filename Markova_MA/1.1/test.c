#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
double f1 (double x)
{
	return x*x + 5*x - 6;
}

int main(void)
{
	double a = -4, b = 2, eps = 0.0001, m;
	printf("x*x + 5*x - 6 ");
	all(f1, a, b, eps);
	return 0;
}


