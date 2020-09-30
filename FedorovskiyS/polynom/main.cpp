#include <iostream>
#include <stdio.h>
#include "math.h"
#include "polynom.h"

using namespace std;

int main(){
    int point_num = 3;
    double *x, *y, *dydx, arg = 10, res;
    x = (double *)malloc(point_num * sizeof(double));
    if(!x){
        printf("Not enough memory!\n");
        return -1;
    }
    y = (double *)malloc(point_num * sizeof(double));
    if(!y){
        printf("Not enough memory!\n");
        free(x);
        return -1;
    }
    dydx = (double *)malloc(point_num * sizeof(double));
    if(!dydx){
        printf("Not enough memory!\n");
        free(x);
        free(y);
        return -1;
    }
    polynom pol;
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;
    y[0] = 0;
    y[1] = 0;
    y[2] = 0;
    dydx[0] = 0;
    dydx[1] = 0;
    dydx[2] = 0;
    res = pol.hermit_res(arg, x, y, dydx, point_num);
    printf("%lf\n", res);
    x[0] = 1;
    x[1] = 2;
    x[2] = 3;
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;
    dydx[0] = 1;
    dydx[1] = 1;
    dydx[2] = 1;
    res = pol.hermit_res(arg, x, y, dydx, point_num);
    printf("%lf\n", res);
    free(x);
    free(y);
    free(dydx);
    printf("Answers are:\n0\n10\n");
    return 0;
}

