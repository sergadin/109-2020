#include "int.hpp"
#include <iostream>
#include <cmath>

int main(void) {
    int n = 10, i;
    ErrorCode perr;
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
    inte p1(x0, y1, n, &perr);
    Y[0] = p1.Y(X, &perr);
    inte p2(x0, y2, n, &perr);
    Y[1] = p2.Y(X, &perr);
    inte p3(x0, y3, n, &perr);
    Y[2] = p3.Y(X, &perr);
    inte p4(x0, y4, n, &perr);
    Y[3] = p4.Y(X, &perr);
    for(i = 0; i < 4; i++) {
        if(perr == I_OK)
            std::cout<<"ideal: "<<ideal[i]<<" result: "<<Y[i]<<std::endl; 
        else if(perr == I_SAME) {
            std::cout<<"Sorry, same points"<<std::endl;  
        }
        else if(perr == I_FEW) {
            std::cout<<"Sorry, too few points"<<std::endl;  
        }
    }
    free(y1);
    free(y2);
    free(y3);
    free(y4);
    return 0;
}

