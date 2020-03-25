typedef double (*RRF) (double x);
double tipainteg(double a, double b, int n, RRF func);
double norminteg(double a, double b, double eps, RRF func);
