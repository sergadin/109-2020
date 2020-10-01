#include <stdio.h>
#include <math.h>
#include "polynom.h"

double polynom::SepDiff(double *x, double *y, double *dydx, int i, int j){
    if(i == j){
        return y[i];
    }
    if(((j - i) == 1) && (i%2 == 0)){
        return dydx[i/2];
    }
    return (polynom::SepDiff(x, y, dydx, i + 1, j) - polynom::SepDiff(x, y, dydx, i, j - 1))/(x[j] - x[i]);
}

double polynom::hermit_res(double arg, double *x, double *y, double *dydx, int point_num){
    double sum = 0, plus;
    for(int i = 0; i < point_num; ++i){
        plus = polynom::SepDiff(x, y, dydx, 0, i);
        for(int j = 0; j < i; ++j){
            plus *= (arg - x[j]);
        }
        sum += plus;
    }
    return sum;
}
