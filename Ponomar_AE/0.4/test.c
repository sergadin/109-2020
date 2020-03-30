#include "stdlib.h"
#include <stdio.h>
#include <math.h>
#include "scalar.h"

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a), (b)), (c)))
#define E 0.0000000001

int multipl_1(int x, int y);
int multipl_2(int x, int y);
int multipl_3(int x, int y);
int sum_1(int x, int y);
int sum_2(int x, int y);
int sum_3(int x, int y);

int main(void)
{
    int N = 3, M = 3, result = 0;
    int x[] = {1, 2, 3};
    int y[] = {10, 9, 8};

    RRF funcs_multipl[] = {multipl_1, multipl_2, multipl_3};
    RRF funcs_sum[] = {sum_1, sum_2, sum_3};

    int true_answer[] = {52, 1331, 1000}; //52=1*10+2*9+3*8 1331=(10+1)*(2+9)*(3+8) 1000=1*1*10*10+2*2*9*9+3*3*8*8

    for(int i = 0; i < M; i++)
    {
        result = scalar(x, y, N, funcs_sum[i], funcs_multipl[i]);
	printf("true: %d real: %d +- %lf\n", true_answer[i], result, E);
        if(abs(result - true_answer[i]) > E * MAX(1, result, true_answer[i]))
            printf("ERROR test %d\n", i+1);
    }
    return 0;
}

int multipl_1(int x, int y)
{
	return x * y;
}

int sum_1(int x, int y)
{
	return x + y;
} 

int multipl_2(int x, int y)
{
    return x + y;
}

int sum_2(int x, int y)
{
	return x * y;
}

int multipl_3(int x, int y)
{
	return x * x * y * y;
}

int sum_3(int x, int y)
{
	return x + y;
}

