#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

double f1 (double x)
{
	return sin(1/x);
}
double f2 (double x)
{
	return exp(x)*sin(1/x);
}
double f3 (double x)
{
	return x*x*x;
}
double f4 (double x)
{
	return (x - 5)*(x - 6)*(x - 7);
}
int main(void)
{
	double a = 0.001, b = 2, m;
	ErrorCode err;
	m = integral(f1, a, b, &err);
	
	printf("f1 ");
	switch(err)
	{
	case INT_NOT:
        printf("FAULT\n");
		break;
	case INT_ND:
		printf("NO DATA\n");
		break;
	case INT_OK:
		printf("Answer = %e\n", m);
	}
	

	printf("f2 ");
	m = integral(f2, a, b, &err);
	
	switch(err)
	{
	case INT_NOT:
        printf("FAULT\n");
		break;
	case INT_ND:
		printf("NO DATA\n");
		break;
	case INT_OK:
		printf("Answer = %e\n", m);
	}
	
	printf("f3 ");
	m = integral(f3, a, b, &err);
	
	switch(err)
	{
	case INT_NOT:
        printf("FAULT\n");
		break;
	case INT_ND:
		printf("NO DATA\n");
		break;
	case INT_OK:
		printf("Answer = %e\n", m);
	}
	
	printf("f4 ");
	m = integral(f4, a, b, &err);
	
	switch(err)
	{
	case INT_NOT:
        printf("FAULT\n");
		break;
	case INT_ND:
		printf("NO DATA\n");
		break;
	case INT_OK:
		printf("Answer = %e\n", m);
	}
	return 0;
}


