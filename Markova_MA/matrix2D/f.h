#include <stdio.h>
#include <stdlib.h>
#include <math.h>
enum
{
    SUCCESS,
	ERROR_USAGE,
	ERROR_MEMORY,
    ERROR_OPEN,
    ERROR_READ, 
	ERROR_MULTY
};

void ved_null(double *a, int n, int m, int ii, int jj, double max);
void change_str(double *a, int n, int m, int i, int j);
void share (double *a, int n, int m, int i, double max);

void print_matrix(double *a, int m, int n);
void ERROR_RE(int ret);

int matr(double *a, int n, int m, double eps);