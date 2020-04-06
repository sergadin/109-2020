typedef double(*RRFUN)(double x);
typedef enum {MIN_OK = 0, MIN_NEOK} ErrorCode;

double  setka (RRFUN function, double epsilon, double a, double b, ErrorCode *error);
