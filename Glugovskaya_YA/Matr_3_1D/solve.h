#include<stdio.h>
#include<stdlib.h>

double DET(double*a,int n);
void MATR_of_ADDITION(double *a, double *MINORS, int n);
double DET_MINOR(double *a, int I, int J, int n);
void TRANS(double *MINORS, int n);