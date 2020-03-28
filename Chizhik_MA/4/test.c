#include <stdio.h>
#include <math.h>

#include "umath.h"
#include "taylor.h"

#define EPS 1e-4

int main(void) {
	char *statusText[] = {
				"OK", 
				"The computation takes too long...",
				"The given value is inappropriate"
			     };
	dFUNC fn[] = {exp, sin, cos, log};
	taylorFUNC approximations[] = {taylor_exp, taylor_sin, taylor_cos, taylor_log};
	double x[] = {-0.7, 0, 0.56, 1, 1.3, 4.5, 25.1};
	
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
			result = (approximations[j])(x[i], EPS, &n, &s);
			expected = (fn[j])(x[i]);
			if (s != OK) {
				fprintf(stdout, "It's hard to compute:\n");
				fprintf(stdout, "%s\n", statusText[s]);
				if (s != BAD_VALUE) {
					fprintf(stdout, "The expected result was %lf and we've got %lf\n", expected, result);
					fprintf(stdout, "And that's normal: our function uses Taylor series expansion at x = 0, but your x = %lf is definitely far from this point\n", x[i]);
				}
			} else {
				fprintf(stdout, "The degree of the last addendum: %d\n", n);
				fprintf(stdout, "Computed: %lf\n", result);
				fprintf(stdout, "Expected: %lf\n", expected);
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
