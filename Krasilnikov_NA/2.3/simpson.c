#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simpson.h"
double simpson(double a, double b, int n, RRFUN function)
{
  double preresult1 = 0, preresult2 = 0, result = 0, x = 0, h;
  int i;
  h = (b - a)/(2 * n);
  for(i = 1, i < n, i += 2)
  {
    x = a + (h * i);
    preresult1 += (*function)(x);
  }
  for(i = 2, i < (n - 1), i += 2)
  {
    x = a + (h * i);
    preresult2 += (*function)(x);
  }
  result = (h/3) * ((*function)(a) + (*function)(b) + 2 * preresult2 + 4 * preresult1)
  return result;
}

double integrate(double a, double b, double epsilon, RRFUN function
{
  int n = 2;
  double res1 = 0, res2 = 0;
	double res1 = simpson(a, b, n, finction), res2 = simpson(a, b, 2*n, function);
	while ((fabs(i2 - i1) > epsilon) && (n < 1000000000))
	{
		result1 = simpson(a, b, n, function);
		n = 2*n;
		result2 = simpson(a, b, n, function);
	}
  if (n < 1000000000)
	return result2;
}
