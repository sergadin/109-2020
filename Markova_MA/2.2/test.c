#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

double f1 (double x)
{
	return x*x + 5*x - 6;
}
double f2 (double x)
{
	return x*x + 1;
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
	double a = -4, b = 2, m;
	ErrorCode err;
	printf("popgк");
	m = integral(f1, a, b, &err);
	
	printf("x*x + 5*x - 6");
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
	
	printf("x*x + 1 = 0 ");
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
	
	printf("x*x*x = 0 ");
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
	
	printf("x*x + 8*x = 0 ");
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


