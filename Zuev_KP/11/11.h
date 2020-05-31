typedef double(*RRFUN)(double t, double x);

double modul(double x);
double integrate(double a, double b, double n, RRFUN ffunc);

