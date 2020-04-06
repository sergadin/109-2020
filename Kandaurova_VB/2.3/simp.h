typedef double(*RRfun)(double x);
typedef enum {I_OK = 0, I_NOSEGM, I_FEW, I_NO} ErrorCode;
double simp(double a, double b, RRfun fun, int n, ErrorCode *perr);
double result(double a, double b, RRfun fun, ErrorCode *perr, double eps);
double mod(double x);
