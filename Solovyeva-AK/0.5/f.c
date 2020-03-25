#include "libs.h"


double search (double f(double),double g(double), double x){
	double tortoise = f(x), hare = f(f(x)); 
	while (g(tortoise) <= 0) {
		tortoise = f(tortoise);
		hare = f(f(hare));
		if (compare(hare, tortoise) || compare(g(hare), g(tortoise))) { 
			return -1;
		} 
		
	}
	return tortoise;
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
