#include <stdio.h>
#include "integral.h"
double f1(double x);
double f2(double x);
double f3(double x);

int main(void) {
    int n = 3; // number of tests
    double eps = 0.0001;
    double integral;

    double a[] = {3, 10, 1};
    double b[] = {9, 12, 2};
    RRfun f[] = {f1, f2, f3};
    for (int k = 0; k < n; k++)
    {
        integral = simpsons_integration(f[k], a[k], b[k], eps);
        printf("Test %d   | integral =  %lf\n ", k, integral);
    }



    return 0;
}

double f1(double x)
{return x*x;} // res: 234

double f2(double x)
{return 0*x;}// res: 0

double f3(double x)
{return x;}// res: 3/2



