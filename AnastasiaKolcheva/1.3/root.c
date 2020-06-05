#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "root.h"

#define MAX_COUNT 10000

int findRoot(double (*func)(double), double a, double b, double epsilon, double* root) 
{
    int counter = 0;
    if (fabs(a - b) < epsilon)
    {
        return E_INVALIDINTERVAL;
    }
    while (fabs(b - a) > epsilon)
    {
        a = b - (b - a) * func(b) / (func(b) - func(a));
        b = a - (a - b) * func(a) / (func(a) - func(b));
        ++counter;
    }
    if (counter > MAX_COUNT)
    {
        return E_TOOMUCHITERATIONS;
    }
    *root = b;
    return S_OK;
}
