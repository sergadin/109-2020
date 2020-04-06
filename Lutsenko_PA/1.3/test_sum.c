#include <stdio.h>
#include <math.h>
#include "sum.h"
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);
void AutoTest(void);



int main (void)


{

    double e [] = {0.1, 0.01, 0.001, 0.01};
    double  answ [] = {-5, 2 , 5.7051, -1};
    double x1 [] = {-6, 0, 2, 0 };
    double x2 [] = {-4, 3, 6, 2 };

    RRFUN f[] = {f1, f2, f3 , f4};
   


    for (int i=0;i<4;i++)
              {
            if (fabs(sum(x1[i], x2[i], e[i], f[i] ) - answ[i])<0,0000001)
                  {printf("OK\n");}
	    else {printf("autotest failed\n'");}

              }
}



double f1 (double a)
{
	return  a + 5;
}

double f2 (double a)
{
        return a*a - 4;
}

double f3 (double a)
{
        return  pow(a,3)- 18*a -83;
}

double f4 (double a)
{
        return a*a*a + 3*a + 3*a*a + 1;
}

















