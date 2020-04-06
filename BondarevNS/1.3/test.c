#include <stdio.h>
#include <math.h>
#include "sum.h"
double f1 (double x);
double f2 (double x);
double f3 (double x);

double f1 (double x)
{
	return  x - 1;
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
double  otvet [] = {1, 0, 0};
double a = -2;
double b = 0;
RRFUN f[] = {f1, f2, f3 };
                 
	for(int i = 0; i < 3; i++)
	{
		res = findRoot(a, b, epsilon, f[i]);
		printf("correct:\n%lf\nmy:\n%lf+-%lf\n", otvet[i], res, epsilon);	
	}
}



