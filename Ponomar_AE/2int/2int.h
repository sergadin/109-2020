typedef double(*RRFUN)(double x);
typedef double(*RRFUN1)(double b);
typedef enum {SF_OK=0, SF_ERROR} ErrorCode;

double integral(double X_a, double X_b, double E, RRFUN func);
double dcsn_f_x(double X_1, double X_2, double E, RRFUN1 func, ErrorCode *error_code);
