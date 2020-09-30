typedef double (*fpointer)(double x);

double newton_method(fpointer f, double a, double b, double eps);
double deriv(fpointer f, double a, double eps);
double sderiv(fpointer f, double a, double eps);
