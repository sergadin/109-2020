#include <stdio.h>
#include <math.h>
#include "integration.h"
#include "../lib/exmath.h"

static double part_sum(double (*f)(double, double), double left, double right, double b); 
static double gaus(double (*f)(double, double), double a, double b, int n);

#define NUMBER 4
#define STEP 2


static double part_sum(double (*f)(double, double), double left, double right, double b)
{
    return ( f(0.2113248654 * right + 0.7886751345 * left, b) + f(0.2113248654 * left + 0.7886751345 * right, b) )  * (right - left)/2; 
}

static double gaus(double (*f)(double, double), double a, double b, int n)
{
    double sum = 0;
    double left, right = a;
    for(int i = 1; i < n; i++)
    {
        left = right;
        right = a + i*(b - a)/n;
        sum += part_sum(f, left, right, b);
    }
    return sum;
}

int integrate(double (*f)(double, double), double a, double b,  double eps, double *x)
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
