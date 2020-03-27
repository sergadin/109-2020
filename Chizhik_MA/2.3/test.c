#include <stdio.h>
#include <math.h>

#include "simpson.h"
#include "umath.h"

#define N 4
#define EPS 1e-7

static double fourty_five(double x) {
	return 45 + 0 * x;
}

static double id(double x) {
	return x;
}

static double sq(double x) {
	return x * x + 3 * x + 2;
}

static double cube(double x) {
	return x * x * x;
}

int main(void) {
	char *statusText[] = {
			"OK", 
			"Method doesn't converge. It seems, this function can't be integrated"
			   };
	double left[] = {1, 5, -1};
	double right[] = {4, 2, 2};

	int i, j, l, r;
	double integral;
	Status s;

	dFUNC funcs[N] = {fourty_five, id, sq, cube};
	double preciseAnswers[][N] = {
			{135, 135, 135},
			{7.5, 10.5, 1.5},
			{49.5, 76.5, 13.5},
			{63.75, 152.25, 3.75}
	};

	l = (int)(sizeof(left) / sizeof(double));
	r = (int)(sizeof(right) / sizeof(double));

	if ((l != r) || (l == 0)) {
		fprintf(stderr, "You have an error in your input, please check it\n");
		return -1;
	}

	for (i = 0; i < N; i++) {
		fprintf(stdout, "Test %d\n\n", i + 1);
		for (j = 0; j < l; j++) {
			fprintf(stdout, "Test %d.%d\n", i + 1, j + 1);
			integral = simpson_integral(funcs[i], left[j], right[j], EPS, &s);
			if (s != OK) {
				fprintf(stdout, "The program can't integrate the given function\n");
			} else {
				fprintf(stdout, "Computed: approximately %lf\n", integral);
				fprintf(stdout, "Expected: %lf\n", preciseAnswers[i][j]);
				if (compareDoubles(integral, preciseAnswers[i][j], EPS) == 0) {
					fprintf(stdout, "The difference is almost unnoticeable\n");	
				} else {
					fprintf(stderr, "Oh no, the program's output is incorrect\n");
					return -2;
				}
			}
		}
	}
	
	fprintf(stdout, "All the tests have been passed successfully, and that's great\n");
	return 0;
}
