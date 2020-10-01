#include <stdio.h>
#include <math.h>

#include "../lib/umath.h"
#include "taylor.h"

#define EPS 1e-3

int main(void) {
	char *statusText[] = {
				"OK", 
				"The computation takes too long...",
				"The given value is inappropriate",
				"The abscissa is too big to get precise answer"
			     };
	dFUNC fn[] = {exp, sin, cos, log};
	taylorFUNC approximations[] = {effective_taylor_exp, effective_taylor_sin, effective_taylor_cos, effective_taylor_log};
	double x[] = {-0.7, 0, 0.56, 1, 1.5, M_E, 3, M_PI, 4.5, 25.1};
	
	double result, expected;
	int i, j, points_len, funcs_len, n;
	Status s;

	points_len = (int)(sizeof(x) / sizeof(double));
	funcs_len = (int)(sizeof(approximations) / sizeof(double));

	if (points_len == 0) {
		fprintf(stderr, "Empty input is a bad thing. Please fix it\n");
		return -1;
	}

	for (j = 0; j < funcs_len; j++) {
		fprintf(stdout, "\nTest %d\n\n", j + 1);
		for (i = 0; i < points_len; i++) {
			fprintf(stdout, "Test %d.%d\n", j + 1, i + 1);
			result = (*approximations[j])(x[i], EPS, &n, &s);
			expected = (*fn[j])(x[i]);
			if (s != OK) {
				fprintf(stdout, "It's hard to compute:\n");
				fprintf(stdout, "%s\n", statusText[s]);
				if (s != BAD_VALUE) {
					fprintf(stdout, "The expected result was %lf and we've got %lf\n", expected, result);
				}
			} else {
				fprintf(stdout, "The degree of the last addendum: %d\n", n);
				fprintf(stdout, "Computed: %.3f\n", result);
				fprintf(stdout, "Expected: %.3f\n", expected);
				if (compareDoubles(result, expected, EPS) == 0) {
					fprintf(stdout, "The difference is inconsiderable\n");
				} else {
					fprintf(stderr, "Something went wrong...\n");
					return -2;
				}
			}
		}
	}

	fprintf(stdout, "We are glad to notice that all the tests have been passed successfully!\n");
	return 0;
}
