#include <stdio.h>
#include <math.h>
#include "find_root.h"
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
    return x-10;
}

double f4(double x)
{
    return tan(x);
}


int main (void)
{
    double x, eps = 1e-16;
    dndFUNC foo[] = {f1, f2, f3, f4};
    double a[] = {-1, 1, 9, -10};
    double b[] = {2, 2.5, 100,10};
    double answers[] = {1, 2, 10, 0};
    int iter, correct = 0;
    
    printf("eps=%0.16lf\n\n", eps);
    
    for(int i = 0; i < 4; i++)
    {
        iter = find_root(foo[i], a[i], b[i], eps, &x);
        if(iter < 0)
        {
            switch(iter)
            {
                case NO_ROOT:
                    printf("in function #%d: same sign [ sgn(a)==sign(b) ]\n", i+1);
                    break;
                case UNABLE:
                    printf("function #%d: this method is incorrect\n", i+1);
                    break;
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
