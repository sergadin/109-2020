#include"stdlib.h"
#include <stdio.h>
#include "scalar.h"


#define  eps 0.00000000001
#define Max2(a,b) ((a)>(b) ? (a) : (b))
#define Max3(a,b,c) (Max2(Max2((a), (b)), (c)))

int module(int x);

int f1_mult(int a, int b);
int f1_add(int a, int b);

int f2_mult(int a, int b);
int f2_add(int a, int b);

int f3_mult(int a, int b);
int f3_add(int a, int b);

int f4_mult(int a, int b);
int f4_add(int a, int b);

// scalar(int *x, int *y, int n, ZZfun addition, ZZfun multiplication)
int main(void)
{
    int n = 5, m = 4; // кол-во аргументов, кол-во тестов
    int x[] = {1, 2, 3, 4, 5};
    int y[] = {6, 7, 8, 9, 10};
    int result = 0;
    ZZZfun funs_multiplication[] = {f1_mult, f2_mult, f3_mult, f4_mult};
    ZZZfun funs_addition[] = {f1_add, f2_add, f3_add, f4_add};

    int right_results[] = {130, 0, 135135, 3628800};


    for(int i = 0; i < m; i++)
    {
        result = scalar(x, y, n, funs_addition[i], funs_multiplication[i]);

        if(module(result - right_results[i]) < eps*Max3(result, right_results[i], 1))
            printf("test %d passed\n", i+1);
        else
            printf("test %d failed\n", i+1);

    }


    return 0;
}

int module(int x)
{
	if(x < 0)
		x = -x;
	return x;
}

int f1_mult(int a, int b)
{return a*b;}
int f1_add(int a, int b)
{return a+b;} // res: 6+14+24+36+50 = 130

int f2_mult(int a, int b)
{
    a=1*a;
    return 0;
}
int f2_add(int a, int b)
{return a+b;} // res: 0

int f3_mult(int a, int b)
{return a+b;}
int f3_add(int a, int b)
{return a*b;} //res: 7*9*11*13*15 = 135135

int f4_mult(int a, int b)
{return a*b;}
int f4_add(int a, int b)
{return a*b;} // res: 6*14*24*36*50 = 3628800


