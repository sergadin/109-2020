typedef double (*RRF) (double x);
double integ(double a, double b, int n, RRF func);
int global(double a, double b, double eps, RRF func);
