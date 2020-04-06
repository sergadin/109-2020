#include<stdio.h>
#include<stdlib.h>
#include"solve.h"
#include"test.h"
#include<math.h>
#define MAX_IT 1e6
#define TooManyIT -1


double solve (double (*f)(double), double a, double b, int n, double eps)
{
	double h = (b - a)/(2*n), s1 = 0, s2 = 4*f(a + h), I2n, In;
	int i, it;
	for (i = 1; i < n; i++)
		{
			s1 += 2*f(a + 2*i*h);
			s2 += 4*f(a + (2*i+1)*h);
		}
	In = (f(a) + f(b) + s1 + s2)*(h/3);
	for (it = 0; it < MAX_IT; it++)
	{	
		n*=2;
		h = (b - a) / (2*n);
		s1 = 0;
		s2 = 4*f(a + h);
		
		for (i = 1; i < n; i++)
		{
			s1 += 2*f(a + 2*i*h);
			s2 += 4*f(a + (2*i+1)*h);
		}
		
		I2n = (f(a) + f(b) + s1 + s2)*(h/3);

		
		if (fabs(I2n-In)/15 < eps) 
		{
			break;
		}
		In=I2n;
	}
	
	if(it >= MAX_IT)
	{
		printf("not found\n");
		return TooManyIT;
	}
	
	return I2n;		
}


