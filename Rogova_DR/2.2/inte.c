#include<math.h>
#include<stdio.h>
#include"inte.h"




double integ(double a, double b, int n, RRF func)
{
	int i;
	double len = (b - a)/n;
	double x1, x2;
	double f1, f2;
	double integall = 0, integnow;
	if((a >= b) || (n < 1))
		return 0;	
	for(i = 0; i < n; i++)
	{
		x1 = a + len * i;
		x2 = x1 + len;
		f1 = (*func)(x1);
		f2 = (*func)(x2);
		integnow = (f1 + f2)*len/2;
		integall += integnow;
	}
	return integall;
}
