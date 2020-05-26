#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 0.0000001


typedef struct value_integral_buf {
    double a;
    double b;
    double value;
} value_integral_buf;
typedef double (*FUN)(double);
double integral(FUN f, double a, double b, double eps);
double root (FUN f, double a, double b, double eps);
double max_2_dbl (double x, double y);
double max_3_dbl (double x, double y, double z);
int compare(double x, double y, double eps);
