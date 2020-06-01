
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "22.h"




double  sum (double x1,double x2,double n,RRFUN f)
{         
           double h,result;
          h = fabs(x2 - x1)/(n);
          int i;
   result += ((*f)(x1) + (*f)(x2)) * h / 2;
   for (i = 1; i < n; ++i)
       {
      result += f(x1 + i * h) * h;
       }
   return result;
          
}



