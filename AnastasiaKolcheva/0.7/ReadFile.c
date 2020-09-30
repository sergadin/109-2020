#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "composition.h"

double f(double x)
{
	return (x - 10);
}

int g(double x, double y)
{
	if ((x * y) > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char** argv)
{
	double x = 100;
	resultFunction(g, f, x);
}
