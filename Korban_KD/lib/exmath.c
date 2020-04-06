#include "../lib/exmath.h"

double f_max(double a, double b, double c)
{
    if(a > b)
    {
        if(a > c)
            return a;
        else
            return c;
    }
    else
    {
        if(b > c)
            return b;
        else
            return c;
    }   
}
