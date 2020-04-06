typedef double(*RRfun)(double x);
typedef enum {I_OK = 0, I_NO} ErrorCode;
double minim(double a, double b, RRfun fun, double eps, ErrorCode *perr);


