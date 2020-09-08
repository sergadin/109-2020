#include <stdio.h>
#include <math.h>
#include "prog3-2.h"
 
double goldenSectionSearch(double a, double b, double eps, fpointer f) 
{
    double phi,x1,x2;
    phi = (1+sqrt(5))/2; 
    
    while (fabs(b-a)>eps) 
    {
    x1 = b - (b-a)/phi;
    x2 = a + (b-a)/phi;
    
    if(f(x1)>=f(x2))
        a = x1;
    else
        b = x2; 
        
    }
    
    return (a + b)/2;   
}
