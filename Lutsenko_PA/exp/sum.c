
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum.h"




double  sum (double x, double eps)
{         
          double e = 1 ;// сумма
    double down = 1;//знаменатель
    double up = 1;//числитель
 
    int i = 1;
    while (fabs(e-expf(x))>eps)
    {
        up = pow(x,i);
        down = factorial(i); //факториал
        e += up / down; //добавление следующего компонента
        i++;
    }

    return e;
 
          
}

 int factorial(int n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}


