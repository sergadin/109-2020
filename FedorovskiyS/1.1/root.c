#include <stdio.h>
#include <math.h>
#include "root.h"
double root(RFun f, double eps, double a, double b, ErrCode *err, int *i){
    double s = 0;
    if(err != NULL){
        *err = OK;
    }
		if(f(a)*f(b) > 0){
            if(err){
                *err = NO_ROOT;
            }
            return s;
        }
    if(fabs(f(a)*f(b)) < 1e-7){
        if(fabs(f(a)) < 1e-7)
            return a;
        else 
            return b;
    }
    while(fabs(a - b) > eps){
        s = a/2 + b/2;
        if (fabs(f(s)) < 1e-7)
            return s;
        if(f(a)*f(s) > 0)
            a = s;
        else 
            b = s;
        *i = *i + 1;
    }
    return s;
}
