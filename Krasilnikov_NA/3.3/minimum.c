#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"minimum.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

double setka (RRFUN function, double epsilon, double a, double b, ErrorCode *error)
{
	int n = 10, i, cofi = 0, memory; //cofi = count_of_iterations
	double h = (b - a)/n, min = (*function)(a), c, A, B, C, min_x;
	*error = MIN_OK;
	while (((b - a) >= epsilon) && (cofi < 7))
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
		else
		{
			if (memory == n)
			{
				a = a + h * (memory - 2);
			}
			else
			{
				c = a;
				a = c + h * (memory - 1);
				b = c + h * (memory + 1);
			}
		}
		n *= 10;
		h /= 10;
		cofi++;
	}
	if ((cofi >= 7) && ((b - a) >= epsilon))
	{
		*error = MIN_NEOK;
		return -1;
	}
	A = 4 * (((*function)(a) + (*function)(b)) / 2 - (*function)((a + b) / 2)) / (a - b) / (a - b);
	B = (4 * (a + b) * (*function)((a + b) / 2) - (a + 3 * b) * (*function)(a) - (3 * a + b) * (*function)(b)) / (a - b) / (a - b);
	C = (*function)(b) - B * b - A * b * b;
	min_x = (-1 * B)/(2 * A);
	if((min_x < a) || (min_x > b))
	{
		if((*function)(a) > (*function)(b))
		{
			return (*function)(b);
		}
		else
		{
			return (*function)(a);
		}
	}
	return (*function)(min_x);
}
