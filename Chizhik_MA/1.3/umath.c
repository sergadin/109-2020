#include <stdio.h>
#include <math.h>

#include "umath.h"

double max(double *arr, int n) {
	double max;
	if (n < 1) {
		max = 0.0;
		return max;
	}
	max = arr[0];
	
	for (int i = 1; i < n; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

int compareDoubles(double a, double b, double precision) {
	double max_candidates[] = {a, b, 1};
	if (fabs(a - b) < precision * max(max_candidates, 3)) {
		return 0;
	}
	if (a > b) {
		return 1;
	}

	return -1;
}

int sgn(double x) {
	if (x > 0) {
		return 1;
	} else if (x < 0) {
		return -1;
	}
	return 0;
}
