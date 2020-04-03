#include<stdio.h>
#include<stdlib.h>
#include"test.h"
#define MAX_IT 1e6

int solve(double a, double b, double eps,double*res,double(*func)(double));