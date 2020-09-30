typedef double (*RFun) (double x);
typedef enum {OK = 0, NO_INT} ErrCode;
double INT(RFun f, double eps, double a, double b, ErrCode *err);
double SUM(RFun f, int N, double a, double b);
