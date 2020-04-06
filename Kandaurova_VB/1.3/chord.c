#include <stdio.h>
#include "chord.h"

double mod(double x){
    if(x < 0)
        return -x;
    else
        return x;
}

double chord(double a, double b, RRfun fun, double eps, ErrorCode *perr){
    double x1 = a, x2 = b, x0, k = 0;
    *perr = I_OK;
    if((a > b)||((b - a) < eps)) 
        *perr = I_NO;
    while(mod(x2 - x1) > eps) {
        x0 = x2 - (x2 - x1) / ((*fun)(x2) - (*fun)(x1)) * (*fun)(x2);
        x1 = x2;
        x2 = x0;
        k++;
        if(k > 10000) {
            *perr = I_NO;
            break;        
        }
    }
    return x2;
}
