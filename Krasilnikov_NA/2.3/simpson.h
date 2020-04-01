typedef double(*RRFUN)(double x);

double simpson(double a, double b, double epsilon, RRFUN ffunc);
double integrate(double a, double b, int n, RRFUN ffunc);
