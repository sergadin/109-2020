typedef double (*RRFUN)(double x);
typedef enum {INT_OK = 0, INT_NOTOK} ErrorCode;

double piece(RRFUN f, double a, double b);
double gauss(RRFUN f, double a, double b, int N);
double integrate(RRFUN f, double a, double b, double eps, ErrorCode *perr);
