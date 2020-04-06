typedef double(*RRFUN)(double x);
typedef enum {MIN_OK = 0, MIN_NEOK} ErrorCode;

struct otrezok
{
  double rightend;
  double leftend;
};


struct otrezok setka (RRFUN function, double epsilon, double a, double b);
