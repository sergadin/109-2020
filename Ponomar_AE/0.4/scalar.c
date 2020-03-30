#include <stdio.h>
#include "scalar.h"

int scalar(int *x, int *y, int N, RRF sum, RRF multipl)
{
    int cur_sum = (*multipl)(x[0], y[0]), summa = cur_sum;
    for (int i = 1; i < N; i++)
    {
        cur_sum = (*multipl)(x[i], y[i]);
        summa = (*sum)(summa, cur_sum);
    }
    return summa;
}
