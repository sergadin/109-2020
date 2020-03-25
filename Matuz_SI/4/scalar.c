#include "scalar.h"

int scalar(int *x, int *y, int n, ZZZfun addition, ZZZfun multiplication)
{
    int current = (*multiplication)(x[0], y[0]);
    int sum = current;
    for (int i=1; i < n; ++i)
    {
        current = (*multiplication)(x[i], y[i]);
        sum = (*addition)(sum, current);
    }
    return sum;
}
