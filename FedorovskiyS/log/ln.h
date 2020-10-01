typedef double (*RFun) (double x);
typedef enum {OK = 0, BAD_APR, NO_RES} ErrCode;
double ln(double eps, double x, ErrCode *err);
