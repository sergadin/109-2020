typedef double(*RRFUN)(double a, double b);

double simp(double a, double b, double n, RRFUN ffunc);
double rung(double a, double b, double ep, RRFUN ffunc);
double modul(double x);

