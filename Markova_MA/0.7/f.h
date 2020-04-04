#define T 30
double f (long double x);
int g (long double x, long double y);

void a (long double (*f)(long double), int (*g)(long double, long double), double x);
