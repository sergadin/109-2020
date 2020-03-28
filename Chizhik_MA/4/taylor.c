#include <stdio.h>
#include <math.h>

#include "umath.h"
#include "taylor.h"

double taylor_recurrent(double x, double precision, int *n, Status *s, dFUNC start_value, diFUNC recurrence) {
	double comp_value, taylor_addendum;

	*n = 1;
	*s = OK;

	comp_value = start_value(x);
	taylor_addendum = start_value(x) * recurrence(x, *n);

	while (compareDoubles(taylor_addendum, 0, precision) != 0) {
		comp_value += taylor_addendum;
		if (*n > 1e2) {
			*s = TOO_LONG;
			return comp_value;
		}

		*n += 1;
		taylor_addendum *= recurrence(x, *n);
	}

	return comp_value;
}


double one(double x) {
	return 1 + 0 * x;
}

double linear(double x, int n) {
	return x / n;
}

double taylor_exp(double x, double precision, int *n, Status *s) {
	return taylor_recurrent(x, precision, n, s, one, linear);
}


double id(double x) {
	return x;
}

double sin_square(double x, int n) {
	return -x * x / (2 * n * (2 * n + 1));
}

double taylor_sin(double x, double precision, int *n, Status *s) {
        return taylor_recurrent(x, precision, n, s, id, sin_square);
}


double cos_square(double x, int n) {
	return -x * x / ((2 * n - 1) * 2 * n);
}

double taylor_cos(double x, double precision, int *n, Status *s) {
        return taylor_recurrent(x, precision, n, s, one, cos_square);
}


double taylor_log(double x, double precision, int *n, Status *s) {
        double real_x = x - 1;
        double comp_value, taylor_addendum;
        *s = OK;
	*n = 1;

	if (compareDoubles(x, 0, precision) != 1) {
                *s = BAD_VALUE;
                return 0;
        }

        comp_value = real_x;
        taylor_addendum = -real_x * real_x / 2;

        while (compareDoubles(taylor_addendum, 0, precision / 2) != 0) {
		comp_value += taylor_addendum;
                if (*n > 50) {
                        *s = TOO_LONG;  
                        return comp_value;
                }

                *n += 1;

		taylor_addendum /= *n + 1;
		taylor_addendum *= -real_x * (*n);
        }

        return comp_value;
}
