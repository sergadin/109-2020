#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

int main(void)
{
	double x, eps, result, sinus;
	while(1)
	{
		printf("input x:\n");
		scanf("%lf", &x);
		printf("input eps:\n");
		scanf("%lf", &eps);
		if(eps < 0)
		{
			break;
		}

		result = f(x,eps);
		printf("RESULT: %lf \n", result);
		sinus = cos(x);
		printf("COS: %lf \n", sinus);
		printf("DIFFERENCE: %lf \n", sinus - result);
	} 
	
	return 0;
}