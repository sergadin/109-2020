#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void a (long double (*f)(long double), int (*g)(long double, long double), double x)
{
	long double ans = (*f)(x);
	int check = 0;
	printf("%Le", ans);
	while(((*g)(ans, (*f)(ans)) > 0) || ((*g)(ans, (*f)(ans)) < 0))
	{
		check++;
		ans = (*f)(ans);
		printf(", %Le", ans);
		if (check > T)
		{
			printf("error ");
			break;
		}
	}
	printf("\n");
}
