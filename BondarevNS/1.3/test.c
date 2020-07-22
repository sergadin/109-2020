#include <stdio.h>
#include <math.h>
#include "root.h"
double f1 (double x);
double f2 (double x);
double f3 (double x);

double f1 (double x)
{
	return  x - 1;
}

double f2 (double x)
{
        return x*x - 4;
}

double f3 (double x)
{
        return  tan(x);
}


int main (void)
{
double res, epsilon = 0.001;
double  otvet [] = {1, 2, 0};
double a = 0;
double b = 3;
RRFUN f[] = {f1, f2, f3 };
                 
	for(int i = 0; i < 3; i++)
	{
		res = findRoot(a, b, epsilon, f[i]);
		printf("correct:\n%lf\nmy:\n%lf+-%lf\n", otvet[i], res, epsilon);	
	}
}




