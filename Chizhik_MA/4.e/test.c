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
	dFUNC fn = exp;
	double x[] = {0.7, 14, 54.1};
	
	double result;
	int i, l, n;
	Status s;

	l = (int)(sizeof(x) / sizeof(double));

	if (l == 0) {
		fprintf(stderr, "Empty input is a bad thing. Please fix it\n");
		return -1;
	}

	for (i = 0; i < l; i++) {
		fprintf(stdout, "\nTest %d\n\n", i + 1);
		result = taylor_exp(x[i], EPS, &n, &s);
		fprintf(stdout, "The degree of the last addendum: %d\n", n);
		if (s != OK) {
			fprintf(stdout, "It's hard to compute with the given precision:\n");
			fprintf(stdout, "%s\n", statusText[s]);
			fprintf(stdout, "The expected result was %lf and we've got %lf\n", fn(x[i]), result);
		} else {
			fprintf(stdout, "Computed: %lf\n", result);
			fprintf(stdout, "Expected: %lf\n", fn(x[i]));
			if (compareDoubles(result, fn(x[i]), EPS) == 0) {
				fprintf(stdout, "The difference is inconsiderable\n");
			} else {
				fprintf(stderr, "Something went wrong...\n");
				return -2;
			}
		}
	}

	fprintf(stdout, "We are glad to notice that all the tests have been passed successfully!\n");
	return 0;
}
