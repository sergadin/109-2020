#include<stdio.h>
#include<stdlib.h>
#include"test.h"
#include<math.h>

static int count = 0;
double func(double x)
{
	count++;
	return sin(x)*x-x*x-3*x*x+10;
}

double func1(double x)
{
	count++;
	return cos(x)+pow(3,x)-10;
}

double func2(double x)
{
	count++;
	return sin(x)+cos(x)*x+4*x+2;
}

int get_count(void)
{
	return count;
}