#include <stdio.h>
#include "simp.h"
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);

double f1(double x) {
	return 2 * x + 4;
}
double f2(double x) {
	return x * x * x + 27;
}
double f3(double x) {
	return cos(x / 10);
}

int main(void) {
    int n = 1000;
	double result, a = 0, b = 1;
	double ideal[] = {5.0, 27.33333, 0.98158};
	RRfun fun[] = {f1, f2, f3};
	for(int i = 0; i < 3; i++) {
		result = simp(a, b, fun[i], n);
		printf("ideal:\n%f\nresult:\n%f\n", ideal[i], result);
	}
    return 0;
}

