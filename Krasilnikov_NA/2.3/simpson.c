#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simpson.h"
double simpson(double a, double b, int n, RRFUN function)
{
	double preresult1 = 0, preresult2 = 0, result = 0, x = 0, h;
	int i;
	h = (b - a)/n;
	for(i = 1; i < n; i += 2)
	{
		x = a + (h * i);
		preresult1 += (*function)(x);
	}
	for(i = 2; i < (n - 1); i += 2)
	{
		x = a + (h * i);
		preresult2 += (*function)(x);
	}
	result = (h/3) * ((*function)(a) + (*function)(b) + 2 * preresult2 + 4 * preresult1);
	return result;
}

struct result  integrate(double a, double b, double epsilon, RRFUN function)
{
	int n = 2;
	double res1 = simpson(a, b, n, function), res2 = simpson(a, b, 2*n, function);
  struct result answer;
	while ((fabs(res2 - res1) > epsilon) && (n < 1000000000))
	{
		res1 = simpson(a, b, n, function);
		n = 2*n;
		res2 = simpson(a, b, n, function);
	}
  answer.rofi = res2;
  answer.n = n;
	rerurn answer;
}
