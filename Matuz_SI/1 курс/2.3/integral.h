#include "math.h"
typedef double(*RRfun)(double x);

struct answer
{
    double integral;
    int n;
};

double integration(RRfun f, double a, double b, int n);
struct answer simpsons_integration(RRfun f, double a, double b, double eps);
double module(double x);