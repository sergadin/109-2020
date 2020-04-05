#include "int.hpp"
#include <iostream>
#include <cmath>

int main(void) {
    int n = 10, i;
    double *y1 = (double *)malloc(n * sizeof(double));
    double *y2 = (double *)malloc(n * sizeof(double));
    double *y3 = (double *)malloc(n * sizeof(double));
    double *y4 = (double *)malloc(n * sizeof(double));
    double *x0 = (double *)malloc(n * sizeof(double));
    double *Y = (double *)malloc(4 * sizeof(double));
    double ideal[] = {0, -1, 1, -0.84147};
    double X = -1;
    for(i = 1; i <= n; i++) {
        y1[i] = 0;
        y2[i] = i;
        y3[i] = i * i;
        y4[i] = sin(i);        
        x0[i] = i;
    }
    inte p1(x0, y1, n);
    Y[0] = p1.Y(X);
    inte p2(x0, y2, n);
    Y[1] = p2.Y(X);
    inte p3(x0, y3, n);
    Y[2] = p3.Y(X);
    inte p4(x0, y4, n);
    Y[3] = p4.Y(X);
    for(i = 0; i < 4; i++) {
        std::cout<<"ideal: "<<ideal[i]<<" result: "<<Y[i]<<std::endl;   
    }
    free(y1);
    free(y2);
    free(y3);
    free(y4);
    return 0;
}

