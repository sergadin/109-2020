#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 0.0000001

typedef double (*FUN)(double);
double search (double f(double),double g(double), double x);
double max_2_dbl (double x, double y);
double max_3_dbl (double x, double y, double z);
int compare(double x, double y);
