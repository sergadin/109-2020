#include <stdio.h>
#include <math.h>
#include "sum.h"
#define E 2,71828
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);
void AutoTest(void);



int main (void)


{

    double e [] = {0,1,0,001, 0,001, 0,0001};
    double  answ [] = {4, -1, 1 , 1.284025};
    double x1 [] = {-1, 0, 0, 1 };
    double x2 [] = {1, 4, 1, 4 };

    RRFUN f[] = {f1, f2, f3 , f4};
   


    for (int i=0;i<4;i++)
              {
            if (fabs(sum(x1[i], x2[i], e[i], f[i] ) - answ[i])<0,001)
                  {printf("OK\n");}
	    else {printf("autotest failed\n'");}

              }
}



double f1 (double a)
{
	return  a * a + 4;
}

double f2 (double a)
{
        return cos (a);
}

double f3 (double a)
{
        return  pow(a,3) - pow(a,2) + a + 1;
}

double f4 (double a)
{
        return expf(1/a) ;
}

















