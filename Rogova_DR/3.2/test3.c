#include<stdio.h>
#include<math.h>
#include"mini.h"



double line(double x);
double sqr(double x);
double zer(double x);






int main(void)
{
	int i, num = 3;
	double res, eps = 0.5;
	double tran[] = {0, 0, 0};
	RRF funcs[] = {line, sqr, zer};
	double a = 1;
	double b = 2;
	for(i = 0; i < num; i++)
	{
		res = mini(a, b, eps, funcs[i]);
		printf("correct:\n%lf\nmy:\n%lf\n", tran[i], res);
	}
}



double line(double x)
{
	return x;
}


double sqr(double x)
{
	return x*x;
}



double zer(double x)
{
	return 0*x;
}
