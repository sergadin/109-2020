
#include <stdio.h>
#include <stdlib.h>
#include "sum.h"


double  sum (double a,RRFUN f,RRFUN g)

{         
          double result = a;
          while ( (*g)( (*f)(result) ) <= 0  ) 
         
             {
                result = (*f)(result);
             }  
  
         return result;
}



