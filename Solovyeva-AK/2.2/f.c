#include "libs.h"

double integral(double f(double), double a, double b, int n) {
	double In = 0, x, dx;
	dx = (b - a ) / n;
	for (int i = 0; i < n; i++) {
		x = a + i * dx;
		In += (f(x) + f(x+dx))/2 * dx;
	}
	return In;
}

double max_2_dbl (double x, double y){
	if (x < y) {
		return y;
	} else {
		return x;
	}
}

double max_3_dbl (double x, double y, double z) {
	return max_2_dbl(max_2_dbl(x,y), z); 
}

int compare(double x, double y) {
	if (fabs(x-y) < (EPS * max_3_dbl(x, y, 1))) {
		return 1;
	} else {
		return 0;
	}
}
