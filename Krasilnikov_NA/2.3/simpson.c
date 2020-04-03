#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simpson.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

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

double integrate(double a, double b, double epsilon, RRFUN function, ErrorCode *error)
{
	int n = 2;
	double res1 = simpson(a, b, n, function), res2 = simpson(a, b, 8*n, function);
	double answer;
	*error = INT_OK;
	while ((fabs(res2 - res1) >= MAXOF3(res1, res2, 1) * epsilon * 0.001) && (n < 100000000))
	{
		res1 = simpson(a, b, n, function);
		n = 8*n;
		res2 = simpson(a, b, n, function);
	}
	if(n >= 9999999)
	{
		*error = INT_NEOK;
	}
	return res2;
}
