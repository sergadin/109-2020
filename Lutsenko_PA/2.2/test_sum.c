#include <stdio.h>
#include <math.h>
#include "sum.h"
#define e 2,71828
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);
void AutoTest(void);



int main (void)


{

    double n [] = {100,1000, 100, 1000};
    double  answ [] = {1.3333, 0.778238, 0.58333 , 7.7734};
    double x1 [] = {1, 0, -1, -1 };
    double x2 [] = {3, 1.5, 0, 1 };

    RRFUN f[] = {f1, f2, f3 , f4};
   


    for (int i=0;i<4;i++)
              {
            if (fabs(sum(x1[i], x2[i], n[i], f[i] ) - answ[i])<0,001)
                  {printf("OK\n");}
	    else {printf("autotest failed\n'");}

              }
}



double f1 (double a)
{
	return  -(a-1)*(a-3);
}

double f2 (double a)
{
        return sin(pow(a,2));
}

double f3 (double a)
{
        return  pow(a,3) + pow(a,2) + a + 1;
}

double f4 (double a)
{
        return pow(2.71828,pow(a,2)) ;
}

















