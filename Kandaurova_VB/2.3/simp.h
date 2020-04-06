typedef double(*RRfun)(double x);
typedef enum {I_OK = 0, I_NOSEGM, I_FEW} ErrorCode;
double simp(double a, double b, RRfun fun, int n, ErrorCode *perr);

