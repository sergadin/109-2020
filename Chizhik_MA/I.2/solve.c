#include <stdio.h>
#include <math.h>

#include "../lib/umath.h"
#include "../2.3/simpson.h"
#include "solve.h"

double f(double t) {
	return 1 / sqrt(1 + pow(t, 4));
}

double f_imp(double z) {
	return 1 / sqrt(pow(cos(z), 4) + pow(sin(z), 4));
}

double solve_equation(double constant, double a, double b, double precision, RootStatus *s) {
	unsigned int closer_to_the_left;
	int counter = 0;
	double tmp, swap, closer_point;
	double left_integral, right_integral, tmp_integral, closer_integral;
	IntStatus i_s;
	*s = OK_ROOT;

	unsigned int a_zero;
	unsigned int b_zero;

        if (a > b) {
                swap = a;
        	a = b;
        	b = swap;
        }

	left_integral = simpson_integral(f_imp, 0, a, precision, &i_s);
	if (i_s != OK_INT) {
		*s = NO_ROOTS;
		return a - 1;
	}
	right_integral = simpson_integral(f_imp, 0, b, precision, &i_s);
	if (i_s != OK_INT) {
		*s = NO_ROOTS;
		return a - 1;
	}


	a_zero = fabs(left_integral - constant) < precision;
	b_zero = fabs(right_integral - constant) < precision;

	if (a_zero || b_zero) {
		return (a_zero) ? a : b;
	}

	if (compareDoubles(a, b, precision) == 0) {
		*s = NO_ROOTS;
		return a - 10 * precision;
	}

	if (sgn(left_integral - constant) == sgn(right_integral - constant)) {
		*s = SAME_SIGN_AT_THE_ENDPOINTS;
		return a - 1;
	}
	
	while(fabs(a - b) > precision) {
		a_zero = fabs(left_integral - constant) < precision;
        	b_zero = fabs(right_integral - constant) < precision;
        	if (a_zero || b_zero) {
                	return (a_zero) ? a : b;
        	}

		if (counter > 1e6) {
			break;
		}
		tmp = b + (right_integral - constant) * (a - b) / (right_integral - left_integral);

		closer_to_the_left = ((tmp - a) < (b - tmp));
		closer_point = closer_to_the_left ? a : b;
		closer_integral = closer_to_the_left ? left_integral : right_integral;

		tmp_integral = closer_integral + simpson_integral(f_imp, closer_point, tmp, precision, &i_s);
		if (i_s != OK_INT) {
			*s = NO_ROOTS;
			return a - 1;
		}

		if ((tmp_integral - constant) == sgn(left_integral - constant)) {
			a = tmp;
			left_integral = tmp_integral;
		} else {
			b = tmp;
			right_integral = tmp_integral;
		}

		counter++;
	}
	
	return a + (b - a) / 2;
}
