#include<stdio.h>
#include<math.h>
#include"mini.h"



double cube(double x);
double somef(double x);
double cosin(double x);






int main(void)
{
	int i, num = 3;
	double res, eps = 0.000001;
	double tran[] = {-1, 0, -19.9};
	RRF funcs[] = {cosin, cube, somef};
	double a = 0;
	double b = 2;
	res = mini(a, b, eps, funcs[2]);
	printf("eps:\n%lf\nmy:\n%lf\n", eps, res);
	
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
	return (x*x*x - x);
}
