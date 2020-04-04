
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f.h"

double f(double x){
    return x;
}


int main(void){
    double a = -1, b = 8, eps = 0.1, x;
    ErrorCode err = OK;
    x = p(f, a, b, eps, &err);
	printf("Точка минимума: %e\n", x);
	if(err)
	{
		printf("error");
	}
	else{
		printf("Точка минимума: %e\n", x);
	}
}
