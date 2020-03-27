#include <stdio.h>
#include <math.h>

#include "umath.h"
#include "secant.h"

void display_amount_of_iterations(int a) {
	fprintf(stdout, "Amount of iterations: %d\n", a);
}

double find_root(dFUNC fn, double a, double b, double precision, Status *s) {
	int counter = 0;
	double tmp, swap;
	*s = OK;

	unsigned int a_zero;
	unsigned int b_zero;

        if (a > b) {
                swap = a;
                a = b;
                b = swap;
        }

	a_zero = fabs(fn(a)) < precision;
	b_zero = fabs(fn(b)) < precision;

	if (a_zero || b_zero) {
		display_amount_of_iterations(counter);
		return (a_zero) ? a : b;
	}

	if (compareDoubles(a, b, precision) == 0) {
		display_amount_of_iterations(counter);
		*s = NO_ROOTS;
		return a - 10 * precision;
	}

	if (sgn(fn(a)) == sgn(fn(b))) {
		*s = SAME_SIGN_AT_THE_ENDPOINTS;
		return a - 1;
	}
	
	while(fabs(a - b) > precision) {
		a_zero = fabs(fn(a)) < precision;
        	b_zero = fabs(fn(b)) < precision;
        	if (a_zero || b_zero) {
                	display_amount_of_iterations(counter);
                	return (a_zero) ? a : b;
        	}

		if (counter > 1e6) {
			break;
		}
		tmp = b + fn(b) * (a - b) / (fn(b) - fn(a));

		if (sgn(fn(tmp)) == sgn(fn(a))) {
			a = tmp;
		} else {
			b = tmp;
		}

		counter++;
	}
	
	display_amount_of_iterations(counter);
	return a + (b - a) / 2;
}
