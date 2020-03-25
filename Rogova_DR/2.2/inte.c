#include<math.h>
#include<stdio.h>
#include"inte.h"

double mod(double x);


double tipainteg(double a, double b, int n, RRF func)
{
	int i;
	double len = (b - a)/n, e = len/10000;
	double x1, x2;
	double f1, f2;
	double integall = 0;
	if((a >= b) || (n < 1))
		return 0;	
	for(i = 1; i < n; i++)
	{
		x1 = a + len * i;	
		f1 = (*func)(x1);
		integall += f1*len;
	}
	integall = integall + 0.5*len*((*func)(a + e) + (*func)(b - e));
	return integall;
}

double mod(double x)
{
	if(x < 0)
		return -x;
	else
		return x;
}



double norminteg(double a, double b, double eps, RRF func)
{
	int i;
	int n = 100, k = 0;
	double i1 = tipainteg(a, b, n, func), i2 = tipainteg(a, b, n, func);
	while((mod(i2 - i1) > eps) && (k < 100))
	{
		k ++;
		n = 2*n;
		i1 = tipainteg(a, b, n, func);
		i2 = tipainteg(a, b, 2*n, func);
	}
	return i2;
}













