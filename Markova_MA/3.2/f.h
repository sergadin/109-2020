#define T 100
double ab (double m);
typedef enum { ER = 1, OK = 0 } ErrorCode;

double gold(double (*f)(double), double a, double b , ErrorCode *perr, double eps);
double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);
