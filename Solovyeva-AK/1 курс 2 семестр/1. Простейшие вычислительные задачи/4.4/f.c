#include "libs.h"

double logarifm(double x, double eps)
{
    int n = 1;
    double sum = x, member = x;
    do {
		member = member*(-1)*x*n/(n+1);
		sum += member;
		n += 1;
    } while (fabs(member) > eps*max_2_dbl(member, 1));
    return sum;
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
