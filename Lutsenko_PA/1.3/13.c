
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "13.h"




double  sum (double prev,double curr,double e,RRFUN f)
{         

          
          double next = 0;
          double tmp;


          do
    {
        tmp = next;
        next = curr - (*f)(curr) * (prev - curr) / ((*f)(prev) - (*f)(curr));
        prev = curr;
        curr = tmp;
    } while (abs(next - curr) > e);
   if ((*f)(prev) == (*f)(curr)) {return f(prev);} 
    return next;
}



