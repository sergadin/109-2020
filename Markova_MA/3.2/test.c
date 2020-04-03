
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f.h"

double f(double x){
    return x*x*x;
}


int main(void){
    double a = 0, b = 8, eps, x;
    ErrorCode err;
    x = p(f, a, b, eps, &err);
	if(err)
	{
		printf("error");
	}
	else{
		printf("Точка минимума: %e", x);
	}
}
