#include <stdio.h>
#include <math.h>
#include "prot.h"
double f0(double x);
double f1(double x);
double f2(double x);

double f0(double x){
    return x*x;
}

double f1(double x){
    return x + 1; 
}

double f2(double x){
    return 2*x;
}
//тесты
int main(void){
    RFun funcs[] = {f0, f1, f2};//вводимые функции, в данном примере посчитается f2(f1(f0(x))).
    int i = 3;//количество функций
    double x = 1;
    x = task (funcs, i, x);
    printf("%lf\n", x);
    return 0;
}

