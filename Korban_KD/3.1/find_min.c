#include <stdio.h>
#include <math.h>
#include "find_min.h"
#include "../lib/exmath.h"

int find_min(dndFUNC f, double a, double b, double eps, double *x)
{
	int it, i;
	double h = (b - a)/NUM, val, val_next;

	i = 0;
	val = f(a);
	for( it = 1; it<MAX_IT; it++ )
	{
		if( i == (int)(NUM) )
		{
            *x = ((*f)(a) < (*f)(b)) ? a : b;
            return NOT_UNIMODAL;
		}

		val_next = f(a + (i + 1)*h);

		if( val>val_next )
		{
			i++;
			val = val_next;
		} 
		else
		{
			if( fabs(h)<eps )
			{
				double prev_val = f(a + (i - 1)*h);
                double prev_x = a + (i - 1)*h, cur_x = a + i*h, next_x = a + (i + 1)*h;
                
                *x = cur_x - ((cur_x - prev_x) * (cur_x - prev_x) * (val - val_next) - (cur_x - next_x) * (cur_x - next_x) * (val - prev_val)) / 
                (2 * ((cur_x - prev_x) * (val - val_next) - (cur_x - next_x) * (val - prev_val)));
                
				return it;
			}

			a = a + i*h;
			i = 0;
			h /= -10;
		}
	}

	return NOT_FOUND;
} 
