#define T 10000000
typedef double(*RRFUN)(double x);

void root(RRFUN f, double a, double b, double eps);
double abcf(RRFUN f, double x);
double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);