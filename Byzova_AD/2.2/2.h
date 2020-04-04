typedef double (*RRFunc) (double x);
double square(double x0, double x1, RRFunc f);
typedef enum {INT_OK = 0, INT_ERROR}
ErrorCode;
double integrate (double a, double b,double eps, int N, RRFunc func, ErrorCode *perr);

