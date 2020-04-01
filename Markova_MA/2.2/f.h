#define eps 0.00001
#define T 1000
typedef enum { INT_OK = 0, INT_NOT, INT_ND } ErrorCode;
double integral(double (*f)(double), double a, double b, ErrorCode *perr, double eps);


double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);