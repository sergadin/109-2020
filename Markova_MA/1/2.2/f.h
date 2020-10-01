#define T 30
#define pi 3.141592653589793238462643

typedef enum { INT_OK = 0, INT_NOT, INT_ND } ErrorCode;
double integral(double (*f)(double), double a, double b, ErrorCode *perr, double eps);
double i (double (*f)(double), double a, double b, int n);

double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);