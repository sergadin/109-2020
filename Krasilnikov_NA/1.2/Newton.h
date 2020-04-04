typedef double(*RRFUN)(double x);
typedef enum {CALC_OK=0, CALC_NEOK} ErrorCode;

struct result
{
  double rofc; //result of calculation
  int iterations;
};

struct result calculation(double a, double b, double epsilon, RRFUN function, ErrorCode *error);
double derivative(RRFUN function, double a, double h);
double second_derivative(RRFUN function, double a, double h);
