
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "f.h"

double f(double x){
    return sin(x);
}


int main(void){
    double a, b, eps, x;
    scanf("%lf %lf %lf",  &a, &b, &eps);
	ErrorCode err;
    x = p(f, a, b, eps, err);
	if(err)
	{
		printf("error");
	}
	else{
		printf("Точка минимума: %e", x);
	}
}
