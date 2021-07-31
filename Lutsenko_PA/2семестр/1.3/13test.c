#include <stdio.h>
#include <math.h>
#include "13.h"
double f1 (double a);
double f2 (double a);
double f3 (double a);
double f4 (double a);
double f5 (double a);
double f6 (double a);
void AutoTest(void);



int main (void)


{

    double e [] = {0.1, 0.1, 0.01, 0.1, 0.001, 0.1};
    double  answ [] = {-5, 2 , 5.7051, -1, 1.1926, 0};
    double x1 [] = {-5, 1.9, 5.6, -2 , 1.1 ,6.25  };
    double x2 [] = {-4.9, 2.1, 6, -1 , 1.2,6.29 };

    RRFUN f[] = {f1, f2, f3 , f4, f5, f6};



    for (int i=0;i<6;i++)
              { 
            if (fabs(sum(x1[i], x2[i], e[i], f[i] ) - answ[i])<e[i] )
                  {printf("\nOK");
                   printf("\nright anwer = %10.6f",answ[i]);
                  printf("\nyour answer = %10.6f",sum(x1[i], x2[i], e[i], f[i]) );}
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

double f5 (double a)
{
        return a*a+a*3-5;
}

double f6 (double a)
{
        return 0;
}














