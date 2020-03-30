#include <math.h>
#include <stdio.h>
#include "decision.1.1.h"

double linear(double x);
double square(double x);
double zero(double x);

int main(void)
{
        int i, num = 3;
        double result, E = 0.001, X_1 = -2, X_2 = 3;
        double true_answer[] = {0, 10000, 10000};
        RRF funcs[] = {linear, square, zero};
        
        for(i = 0; i < num; i++)
        {
                result = dcsn_f_x(X_1, X_2, E, funcs[i]);
                printf("true: %lf real: %lf+-%lf\n", true_answer[i], result, E);
        }
}

double linear(double x)
{
        return x;
}

double square(double x)
{
        return x*x;
}

double zero(double x)
{
        return 0;
}

