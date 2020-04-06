#include <iostream>
#include "int.hpp"

inte::inte(double *a, double *b, int m, ErrorCode *perr) {
    N = m;
    *perr = I_OK;
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
    for(int i = 0; i < N; i++) {
        x[i] = a[i];
        y[i] = b[i];  
    }
}

inte::~inte() {
    free(x);
    free(y);
}

double inte::Y(double X0, ErrorCode *perr) {
    double k, s = 0;
    *perr = I_OK;
    if(N < 1)
        *perr = I_FEW;
    for (int i = 0; i < N; i++) {
        k = 1;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                if(x[i] == x[j]) {
                    *perr = I_SAME;              
                }
                k *= (X0 - x[j]) / (x[i] - x[j]);                
            }
        }
        s += y[i] * k;
    }
    return s;
}
