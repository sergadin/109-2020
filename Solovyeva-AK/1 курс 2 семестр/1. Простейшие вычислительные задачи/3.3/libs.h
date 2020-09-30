#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 0.0001
#define E 2.718281828

typedef struct coefficients {
	double c2;
	double c1;
	double c0;
} coefficients;

typedef struct pair {
	double x;
	double y;
} pair;


typedef double (*FUN)(double);
typedef enum { INT_OK=0, INT_LIMITS, INT_CONVERGENCE } ErrorCode;
double shredding_sizing_grid (double f(double), double a, double b, double eps, ErrorCode *perr);
//pair min_parabola(double c2, double c1, double c0);
//pair min_x_y(double f(double), double x1, double x2, double h); 
coefficients parabola (double f(double), double x1, double x2, double x3);
coefficients gauss(int n, double **matrix_now);
double max_2_dbl (double x, double y);
double max_3_dbl (double x, double y, double z);
int compare(double x, double y, double eps);


