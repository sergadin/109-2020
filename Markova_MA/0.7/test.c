#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double f (double x)
{
	return x*x - 1;
}

int g (double x, double y)
{
	return (int)(x - y);
}

int main(){
    double x = 0.5;
    a(f, g, x);
}
