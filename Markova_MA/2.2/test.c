#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

double f1 (double x)
{
	return pow(x + 1/(x*x + 1) , 1/2);
}
double f2 (double x)
{
	return x;
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
	double a = 0, b = 2*pi, m, eps = 0.00001;
	ErrorCode err;
	m = integral(f1, 1, 10, &err, eps);
	
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
	m = integral(f2, a, b, &err, eps);
	
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
	m = integral(f3, a, b, &err , eps);
	
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
	m = integral(f4, a, b, &err, eps);
	
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


