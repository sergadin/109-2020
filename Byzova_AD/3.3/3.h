typedef double (*RRFunc) (double x);
//double square(double x0, double x1, RRFunc f);
//double solve2 (double a, double b, int N, RRFunc func);
double sign(double a);
double ch(double a, double b, double c);
double minim(double a , double c, double eps, RRFunc f);

typedef enum {INT_OK = 0, INT_ERROR} ErrorCode;

double  minimum(RRFunc f, double eps, double a, double b, ErrorCode *error);
