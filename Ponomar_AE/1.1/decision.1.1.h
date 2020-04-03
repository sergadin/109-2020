typedef double (*RRF)(double x);
typedef enum {SF_OK = 0, SF_ERROR} ErrorCode;
double dcsn_f_x(double X_1, double X_2, double E, RRF func, ErrorCode *error_code);
