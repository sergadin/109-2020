#include <stdio.h>
#include <math.h>
#include "prot.h"
#define EPS 1e-7//погрешность при поиске

double f0(double x);
//double f1(double x);
//double f2(double x);

double f0(double x){
    return (x*x) - 2.;
}

/*double f1(double x){
    return x - 9./8;
}*/

/*double f0(double x){
    return x*x;
}*/
//ответы: корень из двух (1,41421356237), 1.125, No roots.
int main(void){
    double a = 1, b = 2, s;
    s = task(f0, EPS, a, b);
    if((s > b)&&(s > a))
        printf("No roots\n");
    else printf("%lf\n", s);
    return 0;
}

