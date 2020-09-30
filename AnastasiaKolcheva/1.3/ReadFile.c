#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "root.h"

double f(double x)
{
	return (x - 1) * (x - 2) * (x + 3);
}

int main(int argc, char** argv)
{
	double a = 1;
	double b = 1.002;
	double epsilon = 0.0001;
	double root;

	int result = findRoot(sin, a, b, epsilon, &root);

	if (result == S_OK)
	{
		printf("root is %lg\n", root);
	}
	else if (result == E_INVALIDINTERVAL)
	{
		printf("invalid interval\n");
	}
	else if (result == E_TOOMUCHITERATIONS)
	{
		printf("too much iterations\n");
	}
}
