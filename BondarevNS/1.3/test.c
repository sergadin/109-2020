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
        return x*x;
}

double f3 (double x)
{
        return  0*x;
}


int main (void)
{
double res, epsilon = 0.001;
double  otvet [] = {-2, 0, 0};
double a = -3;
double b = 1;
RRFUN f[] = {f1, f2, f3 , f4};
                 
	for(int i = 0; i < 3; i++)
	{
		res = findRoot(a, b, epsilon, f[i]);
		printf("correct:\n%lf\nmy:\n%lf+-%lf\n", otvet[i], res, epsilon);	
	}
}



