#include<stdio.h>
#include<stdlib.h>
#define EPS 1e-15
#define Err_of_Mem 2

int Inverse_matrix(double *a, int n);
double DET(double*a,int n);
void Find_Matr_Dopolneni(double *a, double *MINORS, int n);
double DET_MINOR(double *a, int I, int J, int n);
void TRANS(double *MINORS, int n);