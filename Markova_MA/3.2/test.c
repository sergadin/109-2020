
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f.h"

double f(double x){
    return x;
}


int main(void){
    double a = -1, b = 8, eps, x;
    ErrorCode err;
    x = p(f, a, b, eps, &err);
	printf("Точка минимума: %e", x);
	if(err)
	{
		printf("error");
	}
	else{
		printf("Точка минимума: %e", x);
	}
}
