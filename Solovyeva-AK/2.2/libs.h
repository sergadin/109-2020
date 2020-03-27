#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 0.0001

typedef double (*FUN)(double);
double integral(double f(double), double a, double b, int n);
double max_2_dbl (double x, double y);
double max_3_dbl (double x, double y, double z);
int compare(double x, double y);
