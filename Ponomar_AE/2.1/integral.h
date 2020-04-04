typedef enum {INT_OK = 0, INT_ERROR} ErrorCode;
typedef double (*RRF)(double x);
double integral(RRF func, double X_a, double X_b, double E, ErrorCode *err);

