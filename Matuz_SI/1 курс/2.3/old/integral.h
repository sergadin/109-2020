#include "math.h"
typedef double(*RRfun)(double x);
double integration(RRfun f, double a, double b, int n);
double simpsons_integration(RRfun f, double a, double b, double eps);
double module(double x);