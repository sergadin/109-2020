typedef double(*RRFUN)(double x);

double root(RRFUN f, double a, double b, double eps);
double f1 (double x);