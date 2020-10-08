#include<stdio.h>
#include<stdlib.h>
#define EPS 1e-15
#define Err_of_Mem 2

void solve(double *a, int n, int m);
int choose_string(double *a, int n, int m);
void PoelMax(double *a, int n, int m, int NumMaxPos);