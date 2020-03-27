typedef double (*RRF) (double x);
typedef enum {I_OK = 0, I_BIGN}
ErrorCode;
double norminteg(double a, double b, double eps, RRF func, ErrorCode *error_code);
