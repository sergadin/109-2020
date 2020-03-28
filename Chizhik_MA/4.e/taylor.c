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
	
	while (compareDoubles(taylor_addendum, 0, precision) != 0) {
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

double taylor_sin(double x, double precision, int *n, Status *s) {
        *n = 1;
        double comp_value, taylor_addendum;

        *s = OK;
        comp_value = x;
        taylor_addendum = -x * x * x / factorial(3);

        while (compareDoubles(taylor_addendum, 0, precision) != 0) {
                comp_value += taylor_addendum;
                if (*n > 1e2) {
                        *s = TOO_LONG;  
                        return comp_value;
                }

                *n += 1;
                taylor_addendum *= -x * x / (2 * (*n) * (2 * (*n) + 1));
        }

        return comp_value;
}

double taylor_cos(double x, double precision, int *n, Status *s) {
        *n = 1;
        double comp_value, taylor_addendum;

        *s = OK;
        comp_value = 1;
        taylor_addendum = - x * x / 2;

        while (compareDoubles(taylor_addendum, 0, precision) != 0) {
                comp_value += taylor_addendum;
                if (*n > 1e2) {
                        *s = TOO_LONG;  
                        return comp_value;
                }

                *n += 1;
                taylor_addendum *= -x * x / ((2 * (*n) - 1) * 2 * (*n));
        }

        return comp_value;
}

double taylor_log(double x, double precision, int *n, Status *s) {
        *n = 1;
        double comp_value, taylor_addendum;
        *s = OK;

	if (compareDoubles(x + 1, 0, precision) != 1) {
                *s = BAD_VALUE;
                return 0;
        }

        comp_value = x;
        taylor_addendum = -x * x / 2;

        while (compareDoubles(taylor_addendum, 0, precision) != 0) {
                comp_value += taylor_addendum;
                if (*n > 1e2) {
                        *s = TOO_LONG;  
                        return comp_value;
                }

                *n += 1;
                taylor_addendum *= -x * (*n) / (*n + 1);
        }

        return comp_value;
}
