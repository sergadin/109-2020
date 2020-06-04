#ifndef __READFILE_H___

#define __READFILE_H___
#define S_OK					0
#define E_INVALIDINTERVAL		-1
#define E_TOOMUCHITERATIONS		-2

double f(double x);

int findRoot(double (*func)(double), double a, double b, double epsilon, double* root);


#endif