#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"minimum.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

struct otrezok setka (RRFUN function, double epsilon, double a, double b)
{
	int n = 10, i, cofi = 0, memory; //cofi = count_of_iterations
	double h = (b - a)/n, min = (*function)(a);
	struct otrezok answer;
	while ((b - a) >= epsilon) && (cofi < 100))
	{
		for (i = 0; i <= n; i++)
		{
			if (min >= (*function)(a + h *i))
			{
				min = (*function)(a + h *i);
				memory = i;
			}
		}
		if (memory == 0)
		{
			b = a + h * 2;
		}
		if (memory == n)
		{
			a = a + h * (memory - 2);
		}
		else
		{
			a = a + h * (memory - 1);
			b = a + h * (memory + 1);
		}
		n *= 10;
		h /= 10;
	}
	answer.leftend = a;
	answer.rightend = b;
	return answer;
}
