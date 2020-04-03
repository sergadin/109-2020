#include <stdio.h>
#include <math.h>
#include "sum.h"
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);
double g1 (double a);
double g2 (double a);
double g3 (double a);
double g4 (double a);
void AutoTest(void);



int main (void)


{

    double x [] = {-10, -2, 4, 2};
    double  answ [] = {-4, 4 , 7, 5};

    RRFUN f[] = {f1, f2, f3 , f4};
    RRFUN g[] = {g1, g2, g3 , g4};


    for (int i=0;i<4;i++)
              {
            if (fabs(sum(x[i],f[i],g[i]) - answ[i])<0,0000001)
                  {printf("OK\n");}
	    else {printf("autotest failed\n'");}

              }
}



double f1 (double a)
{
	return  a + 1;
}

double f2 (double a)
{
        return a * a;
}

double f3 (double a)
{
        return  a + 1;
}

double f4 (double a)
{
        return a * a;
}

double g1 (double a)
{
        return  a + 5;
}

double g2 (double a)
{
        return a;
}

double g3 (double a)
{
        return  sin (a);
}

double g4 (double a)
{
        return cos (a);
}















