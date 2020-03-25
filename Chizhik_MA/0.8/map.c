#include <stdio.h>
#include <stdlib.h>
#include "map.h"

double *getResults(dFUNC *funcs, int n, double x) {
    double *arr;
    arr = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        arr[i] = (funcs[i])(x);
    }
    
    return arr;
}
