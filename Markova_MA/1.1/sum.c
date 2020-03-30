#include <stdio.h>
#include "sum.h"

double abcf(RRFUN f, double x)
{
	if ((*f)(x) < 0)
	{
		return -(*f)(x); 
	}
	else
	{
		return (*f)(x);
	}
}
void root(RRFUN f, double a, double b, double eps);
{
	int check = 0;
	double m = (a + b)/2;
	while(abcf(f,m) < eps)
	{
		if((*f)(m) < 0)
		{
			a = (*f)(m);
		}
		else
		{
			b = (*f)(m);
		}
		m = (a + b)/2;
		check++;
		if (check > T)
		{
			printf("FAULT");
			return NULL;
			break;
		}
	}
	printf("\nAnswer = %e\nfunction value = %e\nIterations = %d\n", m, absf(f, m), check);	
}
