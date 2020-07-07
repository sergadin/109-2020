#include <stdio.h>
#include <math.h>
#include "root.h"
#define EPS 1e-7//погрешность при поиске

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
    return x*x + 1;
}*/
//ответы: корень из двух (1,41421356237), 1.125, No roots.
int main(void){
    int i = 0;
    ErrCode err;
    double a = 1, b = 2, res;
    res = root(f0, EPS, a, b, &err, &i);
    printf("%d\n", i);
    if(err == NO_ROOT)
        printf("Coudn't find root!");
    else printf("%lf\n", res);
    return 0;
}

