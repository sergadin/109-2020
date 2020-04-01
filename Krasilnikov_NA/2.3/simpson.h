typedef double(*RRFUN)(double x);

double simpson(double a, double b, int n, RRFUN function);
double integrate(double a, double b, double epsilon, RRFUN function);
