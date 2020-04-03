typedef double (*RRFunc) (double x);
double square(double x0, double x1, RRFunc f);
double solve2 (double a, double b, int N, RRFunc func);


