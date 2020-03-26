#include <stdio.h>
#include "bisec.h"


double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);



int main(void)
{
    double a[] = {50, 1, 2, -2}; //начало интервала
    double b[] = {100, 10, 6, 10}; //конец интервала
    // то есть рассматриваем для i-ой функции интервал [a[i], b[i]]
    RRfun func[] = {f1, f2, f3, f4};
    // double right_roots[] = {51, 3, 0, -1};
    double eps_root = 0.00001;
    double root;
    int n = 4; // кол-во тестов

//double bisection(double a, double b, RRfun func, double eps_root)
    for (int i = 0; i < n; i++)
    {
        if (((*func[i])(a[i])) * ((*func[i])(b[i])) >= 0)
        {
            printf("Test %d failed: Incorrect a and b\n", i+1);
        }
        else 
        {
            root = bisection(a[i], b[i], func[i], eps_root);
            printf("Test %d root:  %lf\n", i+1, root);
        }

    }
    return 0;
}

double f1(double x)
{
    return x-51;
}

double f2(double x)
{
    return x*x-9;
}

double f3(double x)
{
    return 0*x;
}// test failed


double f4(double x)
{
    return x*x*x - 2*x*x + 3;
}