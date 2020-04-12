#include <stdlib.h>
#include "solve.h"

double *func(dFUNC funcs, int n, double *x) {
    double *a;
    a = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        a[i] = (*funcs)(x[i]);
    }
    return a;
}
