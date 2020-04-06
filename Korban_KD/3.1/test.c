#include <stdio.h>
#include <math.h>
#include "find_min.h"
#include "../lib/exmath.h"
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

double f1(double x)
{
    return sin(x-1);
}

double f2(double x)
{
    return x*(x - 2)*(x - 3);
}

double f3(double x)
{
    return -cos(x*10);
}

double f4(double x)
{
    return -x*(x - 2)*(x - 3);
}

#define PRECITION 1e-16

int main (void)
{
    double x, eps = 1e-7;
    dndFUNC foo[] = {f1, f2, f3, f4};
    double a[] = {-1, 1, -0.1, 0};
    double b[] = {2, 3, 0.1,1};
    double answers[] = {-0.57079632625, 2.5485837700000000, 0, 0.7847590650002969};
    int iter, correct = 0;
    
    printf("eps=%0.16lf\n\n", eps);
    
    for(int i = 0; i < 4; i++)
    {
        iter = find_min(foo[i], a[i], b[i], eps, &x);
        if(iter < 0)
        {
            switch(iter)
            {
                case NOT_FOUND:
                    printf("function #%d: iteration count is too hight\n", i+1);
                    break;
                default:
                    printf("function #%d: unknown error", i+1);
            }
            
        }
        if(fabs(x - answers[i]) <= PRECITION*f_max(1, x, answers[i]))
        {
            printf("function #%d x=%lf answer is correct\niterations: %d\n", i+1, x, iter);
            correct++;
        }
        else
            printf("function #%d x=%.16lf answer=%.16lf incorrect\niterations: %d\n", i+1, x, answers[i], iter);
    }
    if(correct == 4)
        printf("all test are succesfull\n");
    else
        printf("not all test are succesfull\n");
    
    return 0;
}
