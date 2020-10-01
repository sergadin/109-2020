typedef double (*RFun) (double x);
typedef enum {OK = 0, NO_MIN} ErrCode;
double min(RFun f, double eps, double a, double b, ErrCode *err);
