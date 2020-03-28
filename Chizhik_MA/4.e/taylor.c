#include <stdio.h>
#include <math.h>

#include "umath.h"
#include "taylor.h"

double taylor_exp(double x, double precision, int *n, Status *s) {
	*n = 1;
	double comp_value, taylor_addendum;
	
	*s = OK;
	comp_value = 1;
	taylor_addendum = x;
	
	while (taylor_addendum > precision) {
		comp_value += taylor_addendum;
		if (*n > 1e2) {
			*s = TOO_LONG;
			return comp_value;
		}

		*n += 1;
		taylor_addendum *= x / *n;
	}
	
	return comp_value;
}
