
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "22.h"




double  sum (double x1,double x2,double eps, int n,RRFUN f)
{         
   double h,prev =0 ,curr = 0;
   h = fabs(x2 - x1)/n;
          
   prev += ((*f)(x1) + (*f)(x2)) * h / 2; //посчитала с разбиением h
   for (int i = 1; i < n; ++i)
   {
      prev += f(x1 + i * h) * h;
   }
    
    h = h/2;
    
    curr += ((*f)(x1) + (*f)(x2)) * h / 2; //посчитала с разбиением h/2
    for (int i = 1; i < n; ++i)
    {
       curr += f(x1 + i * h) * h;
    }
          
    
    while( fabs(prev - curr)/3 >= eps)
    {  //уменьшаю разбиение если нет нужной точности
        h /= 2;
        n *= 2;
        prev = curr;
        curr = 0;
        
        curr += ((*f)(x1) + (*f)(x2)) * h / 2;
        for (int i = 1; i < n; ++i)
        {
           curr += f(x1 + i * h) * h;
        }
    
        

    }
    
    return curr;
}



