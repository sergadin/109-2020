#include "libs.h"

double integral(double f(double), double a, double b, double eps){
	double In1 = 0, In2 = 0;
	double x, dx;
	int n = 2;
	dx = (b - a) / n;
	for (int i = 0; i < n; i++) {
		x = a + i * dx;
		In2 += (f(x) + f(x + dx))/2 * dx;
	}
	n *= 2;
	do {
		In1 = In2;
		In2 = 0;
		dx = (b - a) / n;
		for (int i = 0; i < n; i++) {
			x = a + i * dx;
			In2 += (f(x) + f(x + dx))/2 * dx;
		}
		n *= 2;
	} while ((fabs(In1-In2))/3 >= (eps*max_3_dbl(In1, In2, 1)));
	return In2;
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

int compare(double x, double y, double eps) {
	if (fabs(x-y) < (eps * max_3_dbl(x, y, 1))) {
		return 1;
	} else {
		return 0;
	}
}
