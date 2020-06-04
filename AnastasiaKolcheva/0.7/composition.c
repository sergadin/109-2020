#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "composition.h"


void resultFunction(int (*g)(double, double), double (*f)(double), double x)
{
	int counter = 0;
	double comp = (*f)(x);
	printf("f_0 " "%lg\n", comp);
	int result = (*g)(comp, (*f)(comp));

	while(result != 0)
	{
		++counter;
		comp = (*f)(comp);
		printf("f_""%d = %lg\n", counter, comp);
		result = (*g)(comp, (*f)(comp));
		printf("g_""%d = %d\n", counter, result);
		
		if (counter > MAX_IT)
		{
			printf("too much iterations\n");
			break;
		}
	}
	printf("%d\n", result);
}