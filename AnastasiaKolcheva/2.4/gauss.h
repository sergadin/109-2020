#ifndef __GAUSS_H__

#define __GAUSS_H__

#define S_OK					 0


#define E_INVALIDINTERVAL		-1
#define E_ARGOUTOFRANGE			-2
#define E_NULLREFERENCE			-3

typedef double (*func)(double x);

int gauss(double (*func)(double), double a, double b, int n, double* result);

const char* getErrorMessage(int error);

#endif // !__GAUSS_H__