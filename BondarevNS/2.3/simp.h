typedef double(*RRFUN)(double a);

double integ(double a, double b, double n, RRFUN ffunc);

