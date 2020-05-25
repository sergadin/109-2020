#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "find.h"

double f(double x, double y); //подынтегральная функция
double f(double x, double y) {
    return 1/(sqrt(x * x * x * x + y * y * y * y));
}

double find_root(double a, double eps) {
    if(a < 0 || a >= 1)
        return -1;
    if(a == 0)
        return 1;
    int n = 4, k;
    double integral = 0;
    while(fabs(a - integral) > eps) {
        integral = 0;
        k = 0;
        while(integral < a) {
            k++;
            for(int i = 1; i <= n; i++)
                integral += f((double)i/n,1 + (double)k/n) / n / n;  
        }
        n *= 2;
    }
    return 1 + 2 * (double)k/n;
}
