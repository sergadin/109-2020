#include <stdio.h>
#include <math.h>
#include "INT.h"
double INT(RFun f, double eps, double a, double b, ErrCode *err){
    int N = 100;
    double s = SUM(f, N, a, b), ss = SUM(f, 2*N, a, b);
    if(err){
        *err = NO_INT;
    }
    N = 2*N;
    while(fabs(s - ss) > eps){
        if (N > 1e7){
            return ss;
        }
        s = ss;
        N = 2*N;
        ss = SUM(f, N, a, b);
    }
    if(err)
        *err = OK;
    return ss;
}

double SUM(RFun f, int N, double a, double b){
    double dx = (b/N) - (a/N), s, x = a;
    int j;
    s = dx*f(a)/2 + dx*f(b)/2;//все слагаемые кроме крайних оснований отрезков в сумму попадают без деления на 2.
    x += dx;
    for(j = 0; j < N - 2; ++j){
        s += dx*f(x);
        x += dx;
    }
    return s;
}
