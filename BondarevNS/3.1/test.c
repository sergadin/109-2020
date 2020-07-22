#include <stdio.h>
#include <math.h>
#include "sum.h"




double f1(double x);
double f2(double x);
double f3(double x);



double f1(double x)
{
	return  (x*x*x+x*x-x);
}

double f2(double x)
{
        return (x*x);
}

double f3(double x)
{
        return  (sin(x));
}



int main(void)
{
	double res, epsilon = 0.001;
	double  otvet [] = {0.33333, 0, 0.5};
	double h = 0.0001;
	double x = 0.1;
	RRFUN f[] = {f1, f2, f3 };
                 
	for(int i = 0; i < 3; i++)
	{
		res = Findmin(h, x, epsilon, f[i]);
		printf("correct:\n%lf\nmy:\n%lf+-%lf\n", otvet[i], res, epsilon);	
	}
}



