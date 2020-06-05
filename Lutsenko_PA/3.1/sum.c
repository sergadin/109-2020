
#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include "sum.h"






double sum(double a, double b, RRFUN f, double eps)
{
    int n = 10;
    double h, result,curr, prev, next,zap;
    h = (b - a)/n;
    zap = b-a;
    
    if (h < 2* eps) return -1;
    
    while(  2*h > eps)
    {
        prev = a;
        curr = a + h;
        next = a + h * 2;

        for (int i = 1; i < n - 1; i++)
         {
            if (((*f)(prev) > (*f)(curr)) && ((*f)(next) > (*f)(curr)))
               {
                 a = a + h * (i - 1);
                 b = a + 2 * h;
                 break;
            }
            
            prev = curr;
            curr = next;
            next = next + h;
         }
        n *= 2;
        h = zap / n;
        
    }
    
    if(((*f)(curr) != (*f)(a)) && ((*f)(curr) != (*f)(b)))
    result = vershina(a,b,curr,f);
    else
    result = (*f)(curr);
    
    return result;
  
}




double vershina (double a, double b, double c,RRFUN f )
{
    
  
    double x = c - ((c - a)*(c - a)*((*f)(c) - (*f)(b))-(c - b)*(c - b)*((*f)(c) - (*f)(a)))/2*( (c - a)*((*f)(c) - (*f)(b)) - (c - b)*((*f)(c) - (*f)(a)));
    double y = (*f)(x);
    return y;
}
    
