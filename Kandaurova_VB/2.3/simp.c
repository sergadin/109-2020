#include <stdio.h>
#include "simp.h"
#define maaax(a, b) ((b) > (a) ?  (b) : (a))
#define maax(a, b, c) maaax(maaax((a),(b)), (c))

double mod(double x) {
	if(x < 0)
		return -x;
	else
		return x;
}

double simp(double a, double b, RRfun fun, int n, ErrorCode *perr){
    double h = (b - a)/n, result = 0, left = a, right;
    *perr = I_OK;
    if(a > b)
        *perr = I_NOSEGM;
    if(n < 1)
        *perr = I_FEW;
    right = a + h;
    for(int i = 0; i < n; i++) {
        result += h / 6 * ((*fun)(left) + 4 * (*fun)((left + right)/2) + (*fun)(right));
        right += h;
        left += h;
    }
    return result;
}

double result(double a, double b, RRfun fun, ErrorCode *perr, double eps) {
    int i, n = 100;
    *perr = I_OK;
    double prev , now, p;
    prev = simp(a, b, fun, n / 2, perr);
    now = simp(a, b, fun, n, perr);
    while(mod(prev - now) > eps * maax(1, prev, now)) {
        n *= 2;
        if(n > 10000) {
            *perr = I_NO;
            break;
        }
    }
    printf("n:%d\n", n);
    return now;
}

