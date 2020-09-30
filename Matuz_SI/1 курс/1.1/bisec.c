#include "bisec.h"


int module(int x)
{
    if(x < 0)
        x = -x;
    return x;
}

double bisection(double a, double b, RRfun func, double eps_root)
{
    double root;
    double c = a;
    double length = b - a;
 
   // while ((module(length)-eps_root) > eps_root*Max3(length, eps_root, 1)) // b-a<eps_root
    while (b-a > eps_root)
    {
        c = (a+b)/2;

        
        if ((*func)(c)*(*func)(a) <= 0)
            {
                b = c;
            }
        else
            {
                a = c;
            }
        length = b - a;
    }
    return (a + b)/2;
}
