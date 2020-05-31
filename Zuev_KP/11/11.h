typedef double(*RRFUN)(double t, double x);
typedef double(*RRFUN1)(double b);
typedef enum {SF_OK=0, SF_ERROR} ErrorCode;

double modul(double x);
double integrate(double a, double b, double n, RRFUN ffunc);
double delenie(double a, double b, double ep, RRFUN1 func, ErrorCode *error_code);
