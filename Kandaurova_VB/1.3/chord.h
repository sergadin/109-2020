typedef double(*RRfun)(double x);
typedef enum {I_OK = 0, I_NO} ErrorCode;
double chord(double a, double b, RRfun fun, double eps, ErrorCode *perr);
double mod(double x);
