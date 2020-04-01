#include <math.h>
#include <stdio.h>
#include "min.h"


void Min_Search_Golden_Section(RRfun f, double* a, double* b, double eps)
{
    const double lambda = 0.5 * (sqrt(5) - 1);
    const double mu = 0.5 * (3.0 - sqrt(5));
    double x1, x2 ; //xmin = 0;
    double Fx1, Fx2;


    x1 = *b - lambda * (*b - *a);
    x2 = *a + lambda * (*b - *a);
    Fx1 = (*f)(x1);
    Fx2 = (*f)(x2);
    while ( !stop( *a, *b, eps) ) 
    {
        if (Fx1 > Fx2) 
        {
            *a = x1;
            x1 = x2;
            Fx1 = Fx2;
            x2 = *b - mu*(*b - *a);
            Fx2 = (*f)(x2);
        } 
        else 
        {
            *b = x2;
            x2 = x1;
            Fx2 = Fx1;
            x1 = *a + mu*(*b - *a);
            Fx1 = (*f)(x1);
        } 
    }
    
    //printf("%.10lf");
return;
}

double parabolic_approx(double x1, double x2, double x3, RRfun f)
{
    double approx;
    double F1 = (*f)(x1); 
    double F2 = (*f)(x2); 
    double F3 = (*f)(x3); 
    approx = x2 - 0.5*((x2 - x1)*(x2 - x1)*(F2 - F3) - (x2 - x3)*(x2 - x3)*(F2 - F1))/((x2 - x1)*(F2 - F3) - (x2 - x3)*(F2 - F1));
    return approx;


}

double module(double x)
{
    if(x < 0)
        x = -x;
    return x;
}

int stop(double x0, double x1, double eps)
{
   double xm = 0.5 * module(x1 + x0);

    if (xm <= 1.0)
        return (module(x1 - x0) < eps) ? 1 : 0;
    return (module(x1 - x0) < eps*xm) ? 1 : 0;
}