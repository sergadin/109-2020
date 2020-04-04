#include <stdio.h>
#include "simp.h"

double simp(double a, double b, RRfun fun, int n){
    double h = (b - a)/n, result = 0, left = a, right;
    right = a + h;
    for(int i = 0; i < n; i++) {
        result += h / 6 * ((*fun)(left) + 4 * (*fun)((left + right)/2) + (*fun)(right));
        right += h;
        left += h;
    }
    return result;
}

