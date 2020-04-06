#include <stdio.h>
#include <math.h>
#include "sum.h"
double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);

double f1 (double x)
{
	return  x + 2;
}

double f2 (double x)
{
        return x*x - 4;
}

double f3 (double x)
{
        return  2*x*x - 1;
}

double f4 (double x)
{
        return x*x*x;
}




int main (void)


{

    double epsilon [] = {0.1, 0.01, 0.01, 0.001};
    double  otvet [] = {-2, 2 , 1, 0};
    double a [] = {-3, 0, -1, -1 };
    double b [] = {-1, 3, 2, 1 };

    RRFUN f[] = {f1, f2, f3 , f4};
   


    for (int i=0;i<4;i++)
              {
            if (fabs(findRoot(a[i], b[i], epsilon[i], f[i] ) - otvet[i])<0,0000001)
                  {printf("OK\n");}
	    else {printf("test failed\n");}

              }
}



