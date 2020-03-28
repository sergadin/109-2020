#include<math.h>
#include<stdio.h>
#include"log4.h"


double mod(double x);

double teyl(double x, double eps)
{
	if((x > 1) || (x <= -1))
		return 1000000;
	double tey = x;
	double res = 0;
	int k = 2;
	do
	{
		res += tey;
		tey = tey * (-1) * x * (k - 1)/k;
		k += 1;
	}
	while(mod(tey) > eps);
	return res;

}


double mod(double x)
{
	if(x > 0)
		return x;
	else
		return -x;

}
