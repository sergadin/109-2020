#include <stdio.h>
#include <math.h>

#include "sequence.h"
#include "../lib/umath.h"

#define N 5
#define M 2
#define EPS 1e-3

static double constant(double x) {
	return 4 + 0 * x;
}

static double linear(double x) {
	return 3 * x;
}

static double linear_neg(double x) {
	return -3 * x;
}

static double parabola(double x) {
	return x * x - 4 * x + 3;
}

static double piecewise(double x) {
	if (x > 2) {
		return x + 2;
	}
	return x * x + 1;
}

int main(void) {
	char* statusText[] = {
		"OK",
		"Function is not unimodal here",
	};
	double min;
	Status s;

	dFUNC fn[N] = {constant, linear, linear_neg, parabola, piecewise};
	double segments[M][2] = {
				{-2, 1},
				{4, 1}
			  };
	double preciseAnswers[N][M] = {
				{4, 4},
				{-6, 3},
				{-3, -12},
				{0, -1},
				{1, 4}
	};

	for (int i = 0; i < N; i++) {
		fprintf(stdout, "\nTest %d\n\n", i + 1);
		for (int j = 0; j < M; j++) {
			fprintf(stdout, "Test %d.%d\n", i + 1, j + 1);
			min = find_minimum(fn[i], segments[j][0], segments[j][1], EPS, &s);
			if (s != OK) {
				fprintf(stdout, "%s\n", statusText[s]);
				fprintf(stdout, "But the minimum value is %lf\n", (*fn[i])(min));
				fprintf(stdout, "Expected result: %lf\n", preciseAnswers[i][j]);
				if (compareDoubles((*fn[i])(min), preciseAnswers[i][j], EPS) == 0) {
					fprintf(stdout, "And our computations were absolutely correct!\n");
				} else {
					fprintf(stderr, "Khmmm...\n");
					return -1;
				}
			} else {
				fprintf(stdout, "Computed: %lf\n", (*fn[i])(min));
				fprintf(stdout, "Expected: %lf\n", preciseAnswers[i][j]);
				if (compareDoubles((*fn[i])(min), preciseAnswers[i][j], EPS) == 0) {
					fprintf(stdout, "The difference is inconsiderable\n");
				} else {
					fprintf(stderr, "Something went wrong\n");
					return -2;
				}
			}
		}
	}

	fprintf(stdout, "So, all the tests have been passed successfully. The program's output is correct\n");
	return 0;
}
