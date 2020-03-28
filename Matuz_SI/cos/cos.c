#include "cos.h"
#include <stdio.h>


double my_cosine(double x, double eps)
{
    int k = 1;
    double summ = 1;
    double taylor = 1;
    
    do
    {
	//printf("2");
        taylor = taylor*(-1)*x*x/(k*(k+1));
	summ += taylor;
	k += 2;
    }while (module(taylor)>eps);


    return summ;
}


double module(double x)
{
    if(x < 0)
        x = -x;
    return x;
}