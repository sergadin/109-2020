typedef double(*RRFUN)(double x);

struct result
{
  double rofi //result of integration
  int n
}

double simpson(double a, double b, int n, RRFUN function);
double integrate(double a, double b, double epsilon, RRFUN function);
