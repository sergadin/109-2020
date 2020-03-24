typedef double (*RRF) (double x);
double integ(double a, double b, int n, RRF func);
