#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void a (double (*f)(double), int (*g)(double, double), double x)
{
	double ans = (*f)(x), check = 0;
	printf("%e", ans);
	while(((*g)(ans, (*f)(ans)) > 0) || ((*g)(ans, (*f)(ans)) < 0))
	{
		check++;
		ans = (*f)(ans);
		printf(", %e", ans);
		if (check > T)
		{
			printf("error ");
		}
	}
}
