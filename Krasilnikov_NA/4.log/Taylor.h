typedef double(*RRFUN)(double x);
typedef enum {LOG_OK=0, LOG_NEOK} ErrorCode;

double series(double x, double epsilon, RRFUN function, ErrorCode *error);
 
