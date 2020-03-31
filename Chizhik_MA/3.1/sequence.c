#include <stdio.h>
#include <math.h>

#include "sequence.h"
#include "../lib/umath.h"

double find_minimum(dFUNC f, double a, double b, double precision, Status *s) {
	double step, swap;
	double left, right;
	double prev_x, curr_x, next_x;
	int n = 4;
	double x[3], y[3];
	*s = OK;
	
	if (compareDoubles(a, b, precision) == 0) {
                return a;
        }

	if (a > b) {
		double swap = a;
		a = b;
		b = swap;
	}

	left = a;
	right = b;

	step = (b - a) / n;
	
	while (compareDoubles(step, 0, precision) == 1) {
        	prev_x = left;
        	curr_x = left + step;
        	next_x = curr_x + step;

		for (int i = 1; i < n - 1; i++) {
			if (((*f)(prev_x) > (*f)(curr_x)) && ((*f)(next_x) > (*f)(curr_x))) {
				left += step * (i - 1);
				right = left + 2 * step;

				break;
			}
			prev_x = curr_x;
			curr_x = next_x;
			next_x += step;
		}
		n *= 2;
		step = (b - a) / n;
	}

	if (right - left > 4 * step) {
		*s = NOT_UNIMODAL;
		return ((*f)(a) < (*f)(b)) ? a : b;
	}

	for (int j = 0; j < 3; j++) {
		x[j] = left + j * (2 * step);
		y[j] = (*f)(x[j]);
	}

	return find_parabola_vertex(x, y);
}

double find_parabola_vertex(double *x, double *y) {
	double vertex_value = x[1] - ((x[1] - x[0]) * (x[1] - x[0]) * (y[1] - y[2]) - 
			(x[1] - x[2]) * (x[1] - x[2]) * (y[1] - y[0])) / 
			(2 * ((x[1] - x[0]) * (y[1] - y[2]) - (x[1] - x[2]) * (y[1] - y[0])));

	return vertex_value;
}
