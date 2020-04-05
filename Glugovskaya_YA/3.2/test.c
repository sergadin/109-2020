#include<stdio.h>
#include<stdlib.h>
#include"test.h"
#include<math.h>

double func(double x)
{
	return sin(x);
}

double func1(double x)
{
	return sin(cos(x));
}

double func2(double x)
{
	return 3*x*x - 2*x + 5;
}
