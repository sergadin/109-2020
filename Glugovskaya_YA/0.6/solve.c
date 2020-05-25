#include <stdlib.h>
#include "solve.h"

double *func(dFUNC funcs, int n, double *x, double *y) {
    double *a;
    a = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        a[i] = (*funcs)(x[i], y[i]);
    }
    return a;
}
