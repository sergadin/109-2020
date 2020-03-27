#include <stdio.h>
#include <math.h>

#include "simpson.h"
#include "umath.h"

double integration_with_fixed_step(dFUNC f, double a, double b, int n) {
	double step, x, sum;
	int i, coefficient;

	step = (b - a) / n;
	sum = f(a) + f(b);
	x = a + step;

	for (i = 1; i < n; i++) {
		coefficient = (i % 2 == 0) ? 2 : 4;
		sum += f(x) * coefficient;
		x += step;
	}

	return step * sum / 3;
}

double simpson_integral(dFUNC f, double a, double b, double precision, Status *s) {
	double current_i, prev_i;
	double swap;
	int n;
	*s = OK;

	if (a > b) {
		swap = a;
		a = b;
		b = swap;
	}

	prev_i = integration_with_fixed_step(f, a, b, 2);

	for (n = 4; n < 1e8; n *= 2) {
		current_i = integration_with_fixed_step(f, a, b, n);
		if (compareDoubles(current_i, prev_i, precision) == 0) {
			return current_i;
		}
		prev_i = current_i;
	}

	*s = METHOD_DOES_NOT_CONVERGE;
	return 0;
}
