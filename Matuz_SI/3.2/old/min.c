#include <math.h>
#include "min.h"


void Min_Search_Golden_Section(RRfun f, double* a, double* b, double eps)
{
    const double lambda = 0.5 * (sqrt(5) - 1);
    const double mu = 0.5 * (3.0 - sqrt(5));
    double x1, x2;
    double Fx1, Fx2;


    x1 = *b - lambda * (*b - *a);
    x2 = *a + lambda * (*b - *a);
    Fx1 = (*f)(x1);
    Fx2 = (*f)(x2);
    while ( !stop( *a, *b, eps) ) {
        if (Fx1 > Fx2) {
            *a = x1;
            if (stop(*a, *b, eps))
                break;
            x1 = x2;
            Fx1 = Fx2;
            x2 = *b - mu*(*b - *a);
            Fx2 = (*f)(x2);
        } else {
            *b = x2;
            if (stop(*a, *b, eps))
                break;
            x2 = x1;
            Fx2 = Fx1;
            x1 = *a + mu*(*b - *a);
            Fx1 = (*f)(x1);
        }
    }
return;
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