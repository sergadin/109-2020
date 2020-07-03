#include <stdio.h>
#include <math.h>
#include "prot.h"
double task(RFun f, int N, double a, double b){
    double i = (b/N) - (a/N), s, x = a;
    int j;
    s = i*f(x)/2 + i*f(b)/2;//все слагаемые кроме крайних оснований отрезков в сумму попадают без деления на 2.
    x += i;
    for(j = 0; j < N - 2; ++j){
        s += i*f(x);
        x += i;
    }
    return s;
}
