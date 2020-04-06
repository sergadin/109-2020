#include <stdio.h>
#include <math.h>
#include "integration.h"
#include "../lib/exmath.h"
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

#define PRECITION 1e-10
#define EPSILON 1e-6


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
    return x-10;
}

double f4(double x)
{
    return tan(x);
}


int main (void)
{
    double x, eps = EPSILON;
    dndFUNC foo[] = {f1, f2, f3, f4};
    double a[] = {-1, 1, 9, -10};
    double b[] = {2, 2.5, 15,10};
    double answers[] = {-0.9564497444549821, 0.8906258945147004, 11.9999991010769982, -0.0000007729053253};
    int iter, correct = 0;
    
    printf("eps=%0.16lf\n\n", eps);
    
    for(int i = 0; i < 4; i++)
    {
//         printf("%d\n", i);
        iter = integrate(foo[i], a[i], b[i], eps, &x);
        if(iter < 0)
        {
            switch(iter)
            {
                case -1:
                    printf("function #%d: iteration count is too hight\n", i+1);
                    break;
                default:
                    printf("function #%d: unknown error", i+1);
            }
            
        }
        if(fabs(x - answers[i]) <= PRECITION*f_max(1, x, answers[i]))
        {
            printf("function #%d x=%.16lf answer is correct\niterations: %d\n", i+1, x, iter);
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
