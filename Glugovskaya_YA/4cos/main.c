#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

int main(void)
{
	double x, eps, result, cosinus;
	while(1)
	{
		printf("\n\nInput x in radians:\n");
		scanf("%lf", &x);
		printf("Input eps:\n");
		scanf("%lf", &eps);
		if(eps < 0)
		{
			break;
		}

		result = f(x,eps);
		printf("RESULT: %lf \n", result);
		cosinus = cos(x);
		printf("COS: %lf \n", cosinus);
		printf("DIFFERENCE: %lf \n", fabs(cosinus - result));
	} 
	
	return 0;
}