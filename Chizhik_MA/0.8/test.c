#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define EPS 1e-7

double modulus(double x);
double max(double *arr, int n);
int compareDoubles(double x1, double x2);


static double zero(double x) {
    return 0 * x;
}

static double one(double x) {
    return 0 * x + 1;
}

static double id(double x) {
    return x;
}

static double sq(double x) {
    return x * x;
}

int main(void) {
    double x = 3.56;
    dFUNC funcs[] = {zero, one, id, sq};
    double *stArray;
    int n = (int)(sizeof(funcs) / sizeof(dFUNC));
    valArray = getResults(funcs, n, x);

    for (int i = 0; i < n; i++) {
    	fprintf(stdout, "arr[%d] = %lf\n", i, valArray[i]);
    }

    free(valArray);
    return 0;
}

double max(double *arr, int n) {
    double result = arr[0];
    if (n < 1) {
        return 0;
    }
    if (n == 1) {
        return result;
    }
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > result) {
            result = arr[i];
        }
    }
    
    return result;
}

double modulus(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

int compareDoubles(double x1, double x2) {
    double max_candidates[] = {1, x1, x2};
    if (modulus(x1 - x2) < EPS * max(max_candidates, 3)) {
        return 0;
    } else if (x1 > x2) {
        return 1;
    }
    return -1;
}
