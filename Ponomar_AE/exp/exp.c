#include <stdio.h>
#include <math.h>
#include "exp.h"

double EXPON(double x, double E)
{
    int n = 1;
    double result = 1;
    double tlr = 1;
    
    while(fabs(tlr)>E)
    {
        tlr = tlr*x/n;
	result += tlr;
	n += 1;
    }

    return result;
}

