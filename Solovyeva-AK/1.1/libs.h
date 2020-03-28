#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 0.0000001

typedef double (*FUN)(double);
struct eq root (double f(double), double a, double b, double eps);
double max_2_dbl (double x, double y);
double max_3_dbl (double x, double y, double z);
int compare(double x, double y, double eps);
struct eq {
	double value;
	int quantity;
} eq;
