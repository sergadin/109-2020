#include<stdio.h>
#include<math.h>
#include"mini.h"



double cube(double x);
double somef(double x);
double cosin(double x);






int main(void)
{
	int i, num = 3;
	double res, eps = 0.00000001;
	double tran[] = {-1, -1, -2};
	RRF funcs[] = {cosin, cube, somef};
	double a = -1;
	double b = 4;
	for(i = 0; i < num; i++)
	{
		res = mini(a, b, eps, funcs[i]);
		printf("correct:\n%lf\nmy:\n%lf\n", tran[i], res);
	}
}



double cosin(double x)
{
	return cos(x);
}


double cube(double x)
{
	return x*x*x;
}



double somef(double x)
{
	x*x - 2;
}
