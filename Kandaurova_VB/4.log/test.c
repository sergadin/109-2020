#include <stdio.h>
#include "log.h"
#include <math.h>

int main(void) {
	double x[] = {0.00023, 0.04, -0.97, 56.3};
	double ideal[4];
	double eps = 0.0001, result;
	for(int i = 0; i < 4; i++) {
		ideal[i] = log(1 + x[i]);	
	}
	for(int i = 0; i < 4; i++) {
		if((x[i] >= 1) || (x[i] <= -1))	{
			printf("Sorry, invalid argument\n");		
		}
		else {
			result = taylor(x[i], eps);
			printf("ideal result:%f\nresult:%f\n", ideal[i], result);		
		}
	}
	return 0;
}