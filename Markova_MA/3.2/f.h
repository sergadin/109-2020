#define T 30
typedef enum { ER = 1, OK = 0 } ErrorCode;
double p (double (*f)(double), double x1, double x3, double eps, ErrorCode *perr);

double gold(double (*f)(double), double a, double b, double eps, ErrorCode *perr);
double f(double x);

