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
		if( i >= (NUM) )
		{
			if( fabs(h)<eps )
			{
				*x = a + i*h;
				return it;
			}

			a = a + i*h;
			i = 0;
			h /= -NUM;
		}

		val_next = f(a + (i + 1)*h);

		if( val>val_next )
		{
			i++;
			val = val_next;
		} else
		{
			if( fabs(h)<eps )
			{
				*x = a + i*h;
				return it;
			}

			a = a + i*h;
			i = 0;
			h /= -NUM;
		}
	}

	return NOT_FOUND;
} 
