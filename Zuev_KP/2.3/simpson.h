typedef double(*RRFUN)(double a);

double simp(double a, double b, double ep, RRFUN ffunc);
double modul(double x);
double integrate(double a, double b, double n, RRFUN ffunc);
int obit(int value, int position);
int zbit(int value, int position);
int checkbit(int value, int position);
