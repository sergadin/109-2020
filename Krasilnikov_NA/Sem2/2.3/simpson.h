typedef double(*RRFUN)(double x);
typedef enum {INT_OK = 0, INT_NEOK} ErrorCode;

double simpson(double a, double b, int n, RRFUN function);
double integrate(double a, double b, double epsilon, RRFUN function, ErrorCode *error);
