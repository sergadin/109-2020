
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f.h"

double f1 (double x)
{
	return x*sin(x);
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

int main(void){
    double a = -1, b = 8, eps = 0.001, x;
    ErrorCode err = OK;
    m = gold(f1, a, b, &err, eps);
	
	printf("f1 ");
	switch(err)
	{
	case ER:
        printf("FAULT\n");
		break;
	case OK:
		printf("Answer = %e\n", m);
	}
	

	printf("f2 ");
	m = gold(f2, a, b, &err, eps);
	
	switch(err)
	{
	case ER:
        printf("FAULT\n");
		break;
	case OK:
		printf("Answer = %e\n", m);
	}
	
	printf("f3 ");
	m = gold(f3, a, b, &err , eps);
	
	switch(err)
	{
	case ER:
        printf("FAULT\n");
		break;
	case OK:
		printf("Answer = %e\n", m);
	}
	
	printf("f4 ");
	m = gold(f4, a, b, &err, eps);
	
	switch(err)
	{
	case ER:
        printf("FAULT\n");
		break;
	case OK:
		printf("Answer = %e\n", m);
	}
}
