#include <stdio.h>

#include "umath.h"
#include "secant.h"

#define EPS 1e-7
#define N 4

static double zero(double x) {
	return 0 * x;
}

static double three(double x) {
	return 3 + 0 * x;
}

static double linear(double x) {
	return 2 * x - 7;
}

static double quadratic(double x) {
	return x * x - 1;
}

int main(void) {
	double left[] = {-1, 0, 6, 0};
	double right[] = {-1, 5, 3, 1};
	double root;

	dFUNC fnArr[N] = {zero, three, linear, quadratic};
	double preciseAnswers[][N] = {
		{-1, -5e4, 3.5, -1},
		{0, 60, 3.5, 1},
		{3, 0, 3.5, 1},
		{0, -4.76, 3.5, 1}
	};
	int n, l, r;

	n = (int)(sizeof(fnArr) / sizeof(dFUNC));
	l = (int)(sizeof(left) / sizeof(double));
	r = (int)(sizeof(right) / sizeof(double));

	if (l != r) {
		fprintf(stderr, "You have an error in your input. Please check it\n");
		return -1;
	}

	for (int i = 0; i < N; i++) {
		fprintf(stdout, "Test %d\n\n", i + 1);
		for (int j = 0; j < l; j++) {
			fprintf(stdout, "Test %d.%d\n", i + 1, j + 1);
			root = find_root(fnArr[i], left[j], right[j], EPS);
			if ((root - left[j]) * (right[j] - root) < 0) {
                                fprintf(stdout, "The program is unable to find a root here\n");
				if ((preciseAnswers[j][i] - left[j]) * (right[j] - preciseAnswers[j][i]) < 0) {
					fprintf(stdout, "And it is absolutely great since there's really no roots\n");
				} else {
					fprintf(stderr, "And that's our fault. We're sorry");
					return -2;
				}
                        } else {
                                fprintf(stdout, "Equation has a root: %lf\n", root);
				fprintf(stdout, "And the precise answer is: %lf\n", preciseAnswers[j][i]);
				if (compareDoubles(root, preciseAnswers[j][i], EPS) == 0) {
					fprintf(stdout, "The difference is almost unnoticeable\n");
				} else {
					fprintf(stderr, "What a pity! The difference's too big\n");
					return -2;
				}
                        }

		}	
	}

	fprintf(stdout, "All the tests have been passed successfully, and that's great\n");
	return 0;
}
