typedef enum { INT_OK, INT_NOT, INT_ND } ErrorCode;
double integral(double (*f)(double), double a, double b, ErrorCode *perr);


double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);