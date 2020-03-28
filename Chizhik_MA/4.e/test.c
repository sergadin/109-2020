#include <stdio.h>
#include <math.h>

#include "umath.h"
#include "taylor.h"

#define EPS 1e-4

int main(void) {
	char *statusText[] = {
				"OK", 
				"The computation takes too long..."
			     };
	dFUNC fn[] = {exp, sin, cos, log};
	taylorFUNC approximations[] = {taylor_exp, taylor_sin, taylor_cos, taylor_log};
	double x[] = {-1.3, 0.7, 14, 25.1};
	
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
			expected = (j == 3) ? (fn[j])(x[i] + 1) : (fn[j])(x[i]);
			fprintf(stdout, "The degree of the last addendum: %d\n", n);
			if (s != OK) {
				fprintf(stdout, "It's hard to compute with the given precision:\n");
				fprintf(stdout, "%s\n", statusText[s]);
				fprintf(stdout, "The expected result was %lf and we've got %lf\n", expected, result);
			} else {
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
