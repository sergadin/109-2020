#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double f (double x)
{
	printf("%e ," x*x);
	return 1/(x*x);
}

int g (double x, double y)
{
	return (int)(x - y);
}

int main(){
    double x = 1;
    a(f, g, x);
}
