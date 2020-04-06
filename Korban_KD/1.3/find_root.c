#include <stdio.h>
#include <math.h>
#include "find_root.h"
#include "../lib/exmath.h"



int find_root(dndFUNC f, double a, double b, double eps, double *x)
{
	int it;
	double c, val_c, val_a = f(a), val_b = f(b);
    
    if(val_a*val_b > 0)
        return NO_ROOT;

    if( fabs(val_a) < eps || fabs(val_b) < eps )
    {
        if(fabs(val_a) < fabs(val_b) )
            *x = a;
        else 
            *x = b;
        return 0;
    }
    
    if(a > b)
    {
        double temp = a;
        a = b;
        b = temp;
    }
    
    
	for( it = 1; it<MAX_IT; it++ )
	{
        
        if (fabs(val_a - val_b) < eps)
        {
            return UNABLE;
        }
        
        if ( fabs((b - a)/(val_b - val_a))<eps )
        {
            return UNABLE;
        }
        
		c = a - val_a*(b - a)/(val_b - val_a);

		val_c = f(c);

		if( fabs(val_c)<eps )
		{
			*x = c;
			return it;
		}

		if( ( fabs(a - c)<=PRECITION*f_max(a, c, 1) ) || ( fabs(b - c)<=PRECITION*f_max(b, c, 1) ) )
			break;

		if( val_a*val_c<=0 )
		{
			b = c;
			val_b = val_c;
		}
		else
		{
			a = c;
			val_a = val_c;
		}
	}
    *x = c;
	return NOT_FOUND;
}
