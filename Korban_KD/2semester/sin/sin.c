#include <math.h>
#include "sin.h"

double _sin(double x, double eps)
{
	int flag_sign = 0, i;
	double res, item;

	if( x<0 )
	{
		x *= -1;
		flag_sign = 1;
	}

	x -= floor( x/(2*M_PI) )*2*M_PI;

	if( x>M_PI )
	{
		x -= M_PI;
		flag_sign += 1;
	}

	if( x>1 )
	{
		x -= M_PI/2;

		if( x<0 )
			x *= -1;

		item = 1;
		res = 1;
		for( i = 1; item>eps; i++ )
		{
			item *= x*x/( (2*i - 1)*2*i );

			if( i%2 )
				res -= item;
			else
				res += item;
		}
	} else
	{
		item = x;
		res = x;
		for( i = 1; item>eps; i++ )
		{
			item *= x*x/( 2*i*(2*i + 1) );

			if( i%2 )
				res -= item;
			else
				res += item;
		}
	}

	if( flag_sign&1 )
		res *= -1;

	return res;
}
