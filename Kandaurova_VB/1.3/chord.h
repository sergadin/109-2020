typedef double(*RRfun)(double x);
typedef enum {I_OK = 0, I_NOSIGM, I_SMALL, I_MUCH} ErrorCode;
double chord(double a, double b, RRfun fun, double eps, ErrorCode *perr);
double mod(double x);
