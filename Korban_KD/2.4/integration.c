#include <stdio.h>
#include <math.h>
#include "integration.h"
#include "../lib/exmath.h"



double part_sum(dndFUNC f, double a, double b)
{
    return ( f(0.2113248654 * b + 0.7886751345 * a) + f(0.2113248654 * a + 0.7886751345 * b) )  * (b - a)/2; 
}

double gaus(dndFUNC f, double a, double b, int n)
{
    double sum = 0;
    double left, right = a;
    for(int i = 1; i < n; i++)
    {
        left = right;
        right = a + i*(b - a)/n;
        sum += part_sum(f, left, right);
    }
    return sum;
}

int integrate(dndFUNC f, double a, double b,  double eps, double *x)
{
    double integ1 = gaus(f, a, b , NUMBER), integ2;
    for(int n = NUMBER * STEP; n < 1073741824; n *= STEP)
    {

        integ2 = gaus(f, a, b , n);
        
        if(fabs(integ1 - integ2) < eps*f_max(1, integ1, integ2))
        {
            *x = integ2;
            return n;
        }
        
        integ1 = integ2; 
    }
    *x = integ2;
    return -1;
}
