#include <stdio.h>
#include <math.h>
#include "sum.h"
void AutoTest(void);
#define EPS 1e-7


int main (void)


{

    double e [] = {0.0001,0.001, 0.01, 1};
    //double  answ [] = {0.135335, 1,20.08553 , 148.41315};
    double x [] = {-2, 0, 3, 5 };
   


    for (int i=0;i<4;i++)
              {
            if (fabs(sum( x[i], e[i] ) - expf(x[i])) < e[i])
                  {printf("OK\n");}
	    else {printf("autotest failed\n'" );}

              }
}

















