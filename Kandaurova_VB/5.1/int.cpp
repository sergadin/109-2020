#include <iostream>
#include "int.hpp"

inte::inte(double *a, double *b, int m) {
    N = m;
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

double inte::Y(double X0) {
    double k, s = 0;
    for (int i = 0; i < N; i++) {
        k = 1;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                if(x[i] == x[j]) {
                    std::cout<<"Sorry"<<std::endl;              
                }
                k *= (X0 - x[j]) / (x[i] - x[j]);                
            }
        }
        s += y[i] * k;
    }
    return s;
}
