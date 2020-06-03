#include <stdio.h>
#include <math.h>
#include "sum.h"
#define E 2,71828
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);




int main (void)


{

    double e [] = {0.1,0.001, 0.01, 0.01};
    double  answ [] = {5, -1, 1 , -4};
    double x1 [] = {-1, 0, 0, -3 };
    double x2 [] = {1, 4, 1, 1 };

    RRFUN f[] = {f1, f2, f3 , f4};
   


    for (int i=0;i<4;i++)
              {
             printf("результат=%f\n",sum(x1[i], x2[i], f[i], e[i] ));
	         printf("правильный ответ=%f\n'",answ[i]);

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
        return a-1 ;
}

















