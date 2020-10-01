typedef double (*RFun) (double x);
typedef enum  {OK = 0, NO_ROOT} ErrCode;
double root(RFun f, double eps, double a, double b, ErrCode *err, int *i);
