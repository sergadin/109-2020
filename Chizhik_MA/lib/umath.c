#include <stdio.h>
#include <math.h>

#include "umath.h"

int factorial(int n) {
	int result = 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}
	return result;
}

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

void swap(double *a, double *b) {
	double swap = *a;
	*a = *b;
	*b = swap;
}

int perm_sign(int *arr, int n) {
	int sign = 1;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) {
				sign *= -1;
			} else if (arr[i] == arr[j]) {
				return 0;
			}
		}
	}
	return sign;
}

void inverse(int *arr, int n) {
	for (int i = 0; i < n / 2; i++) {
		int swap = arr[i];
		arr[i] = arr[(n - 1) - i];
		arr[(n - 1) - i] = swap;
	}
}
