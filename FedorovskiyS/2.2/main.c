#include <stdio.h>
#include <math.h>
#include "prot.h"

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
    double a = 1, b = 2, s;//а - начало интегрирования, b - конец.
    int N = 1000;
    s = task(f0, N, a, b);
    printf("%lf\n", s);
    return 0;
}

