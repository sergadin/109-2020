#include<stdio.h>
#include<stdlib.h>
#include"test.h"
#include"solve.h"
#include<math.h>
#define MAX_IT 1e6
#define TooManyIT -1

int solve(double a, double b, double eps, double*res, double(*func)(double))
{
	int it;
	double l, m, fl, fm, t, x;
	t = (1 + sqrt(5)) / 2;
	
	l = b - (b-a) / t;
	m = a + (b-a) / t;
	
	fl = func(l);
	fm = func(m);
	
	for(it = 0; it < MAX_IT; it++)
	{	
		if(fabs(b - a) <= eps)
		{
			break;
		}
		
		if(fl >= fm)
		{
			a = l;
			l = m;
			m = a + (b-a) / t;
			fl = fm;
			fm = func(m);
		}
		else
		{
			b = m;
			m = l;
			l = b - (b-a) / t;
			fm = fl;
			fl = func(l);
		}
	}
	
	if(it >= MAX_IT)
	{
		printf("cannot found\n");
		return TooManyIT;
	}
	x = (b+a) / 2;
	
	if ((func(a) > func(x)) && func(x) < func(b))
	{
		x = x - ((x-a)*(x-a)*(func(x) - func(b)) - (x - b) * (x - b) * (func(x) - func(a)))/(2 * ((x - a) * (func(x) - func(b)) - (x - b) * (func(x) - func(a))));
		printf("\nmin=(%lf,", x);
		*res = func(x - ((x-a)*(x-a)*(func(x) - func(b)) - (x - b) * (x - b) * (func(x) - func(a)))/(2 * ((x - a) * (func(x) - func(b)) - (x - b) * (func(x) - func(a)))));
	}
	else
	{
		printf("\nmin=(%lf,", (b+a) / 2);
		*res = (func)(x);
	}
	
	return 0;
}