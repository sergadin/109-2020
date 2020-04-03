typedef double(*RRFUN)(double x);

struct result
{
  double rofc; //result of calculation
  int iterations;
};

struct result calculation(double a, double b, double epsilon, RRFUN function);
