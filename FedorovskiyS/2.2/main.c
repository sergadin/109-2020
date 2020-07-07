#include <stdio.h>
#include <math.h>
#include "INT.h"

double f0(double x);
//double f1(double x);
//double f2(double x);

double f0(double x){
    return x*x - 2.;
}

/*double f1(double x){
    return x - 9./8;
}*/

/*double f0(double x){
    return x*x*x;
}*/
//ответы: 1/3 или 0,(3); 0,375; 3,75;
int main(void){
    double a = 1, b = 2, s, eps = 1e-6;//а - начало интегрирования, b - конец.
    ErrCode err;
    s = INT(f0, eps, a, b, &err);
    if(err == NO_INT)
        printf("Coudn't find integral!");
    else
        printf("%lf\n", s);
    return 0;
}

