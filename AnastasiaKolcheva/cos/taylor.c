#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "taylor.h"


void test(double epsilon, const char* name, double (*taylor)(double, double), double (*library)(double))
{
	int index;
	double x[] = { M_PI / 2, M_PI / 3, M_PI / 4, M_PI / 5, M_PI / 6, M_PI / 7, M_PI / 8 };
	printf("\n-------------------------------- epsilon = %g --------------------------------\n", epsilon);
	for (index = 0; index < sizeof(x) / sizeof(double); ++index)
	{
		double yt = taylor(x[index], epsilon);
		double yl = library(x[index]);
		printf("%s(%f) : |T - L| = DELTA : | %12.10f - %12.10f | = %12.6g \n", name, x[index], yt, yl, fabs(yt - yl));
	}
	
}
 

double taylorSin(double x, double epsilon)
{
	int index;
	double nth = x;
	double sum = nth;
	for (index = 1; ; ++index)
	{
		nth = nth * (-1) * x * x / (2.0 * index) / (2.0 * index + 1);
		if (fabs(nth) <= epsilon || fabs(nth) <= 1E-100)
		{
			break;
		}
		sum += nth;
	}
	return sum;
}


double taylorCos(double x, double epsilon)
{
	int index;
	double nth = 1;
	double sum = nth;
	for (index = 1; ; ++index)
	{
		nth = nth * (-1) * x * x / (2.0 * index - 1) / (2.0 * index);
		if (fabs(nth) <= epsilon || fabs(nth) <= 1E-100)
		{
			break;
		}
		sum += nth;
	}
	return sum;
}

