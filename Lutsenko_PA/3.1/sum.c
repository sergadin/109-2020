
#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include "sum.h"






double sum(double a, double b, RRFUN f, double eps)
{

    int n = 150;
    double h,min,result;
    int index_min=0;
    h = (b - a)/n;
    
    while (h>eps)
    {
      min=a;
    for (int k=0;k<=n;k++)
    {
        if ((*f)(a+k*h)<min )
        {
            min = (*f)(a+k*h);
            index_min=k;
        }
    }
    a = a + (index_min-1)*h;
    b = a + (index_min+1)*h;
        h=h/2;
        
    }
    if(((*f)(a + index_min*h) != (*f)(a)) && ((*f)(a + index_min*h) != (*f)(b)))
    result = vershina(a, a + index_min*h,b,f);
    else
    result = (*f)(a + index_min*h);
    
    return result;
  
}




double vershina (double a, double b, double c,RRFUN f )
{
    
  
    double x = c - ((c - a)*(c - a)*((*f)(c) - (*f)(b))-(c - b)*(c - b)*((*f)(c) - (*f)(a)))/2*( (c - a)*((*f)(c) - (*f)(b)) - (c - b)*((*f)(c) - (*f)(a)));
    double y = (*f)(x);
    return y;
}
    
