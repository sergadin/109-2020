typedef double(*RRfun)(double x);

void Min_Search_Golden_Section(RRfun f, double* a, double* b, double eps);
double parabolic_approx(double x1, double x2, double x3, RRfun f);

double module(double x);
int stop(double x0, double x1, double eps);