typedef double (*RRF)(double x);
typedef enum {SF_OK = 1, SF_ERROR} ErrorCode;
double integral(RRF func, double X_a, double X_b, double E, ErrorCode *error_code);

