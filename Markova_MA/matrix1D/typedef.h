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

int read_matrix(double *a, int m, int n, const char *name);
void print_matrix(double *a, int m, int n);
void ERROR_RE(int ret, char *name);

int rank(double *a, int n, int m);