/*#define  EPS 0.00000000001
#define Max2(a,b) ((a)>(b) ? (a) : (b))
#define Max3(a,b,c) (Max2(Max2((a), (b)), (c)))*/
typedef double(*RRfun)(double x);
int module(int x);
double bisection(double a, double b, RRfun func, double eps_root);
