#include <stdio.h>
#include <math.h>
#include "prot.h"
double task(RFun f, double eps, double a, double b){
    double s;
    if((f(a)*f(b)) > 0){
        return fabs(a) + fabs(b) + 1;
    }
    if((f(a)*f(b)) == 0){
        if(f(a) == 0)
            return a;
        else return b;
    }
    while(fabs(a - b) > eps){
        s = a/2 + b/2;
        if (f(s) == 0)
            return s;
        if(f(a)*f(s) > 0)
            a = s;
        else b = s;
    }
    return a;
}
