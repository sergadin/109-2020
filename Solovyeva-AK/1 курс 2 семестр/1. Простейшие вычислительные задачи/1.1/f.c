#include "libs.h"

struct eq root (double f(double), double a, double b, double eps){
	double t, f1, f2;
	struct eq equation;
	equation.quantity = 0;
	if (f(a)*f(b) > 0) {
		equation.value = -1;
		equation.quantity = 0;
		return equation;
	}
    do {
		equation.quantity++;
		f1 = f(a);
		t = (a + b)/2;
		f2 = f(t);
		if (f1 * f2 <= 0) {
			b=t;
		} else {
			a = t;
		}
	} while (compare(a,b,eps));
    equation.value = (a + b)/2;
    f1 = f(equation.value);
	return equation;
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
	if (fabs(x-y) < (eps* max_3_dbl(x, y, 1))) {
		return 1;
	} else {
		return 0;
	}
}

