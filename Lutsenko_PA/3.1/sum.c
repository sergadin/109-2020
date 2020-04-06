
#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include "sum.h"
#define PI 3.1415926536


 

 
double sum (double x,double pogr, double h, RRFUN f) {
 
    
    if (x==0) {x+=0.1;}
    while ((f(x+h)-2*f(x)+f(x-h))/(h*h)<=0) {x+=0.1;}
    double x1;
    x1=x-0.5*h*(f(x+h)-f(x-h))/(f(x+h)-2*f(x)+f(x-h));
    while (fabs(x1-x)>pogr) {
        x=x1;
        x1=x-0.5*h*(f(x+h)-f(x-h))/(f(x+h)-2*f(x)+f(x-h));
    }
    return (*f)(x1);
    
   }
