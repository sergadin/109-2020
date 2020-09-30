#include<stdio.h>
#include<math.h>
#include "prot.h"
double task(RFun *a, int n, double x){
    int i;
    for(i = 0; i < n; ++i){
        x = a[i](x);
    }
    return x;
}
