#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "integral.h"

double integral(RRF func, double X_a, double X_b, double E, ErrorCode *error_code)
{
	double result = 0, dx = (X_b-X_a)*E;
	for (int i = 0; i < 1/E; i++)
       	{
		result += func(X_a + dx * (i + 0.5));
	}
	 
	result = result * dx;
	
	return result;
}

