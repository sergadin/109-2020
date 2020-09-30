#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long double f (long double x)
{
	return 1/(x*x - 3*x - 4);
}

int g (long double x, long double y)
{
	double eps = 0.01;
	if((x - y) < eps && (- x + y) < eps)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int main(){
    double x = 0.5;
    a(f, g, x);
}
