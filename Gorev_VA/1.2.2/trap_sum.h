#define eps 0.000001
#define pi 3.141592653589793238462643

double trap_sum(double (*f) (double), double a, double b, int N);
double integral(double (*f) (double), double a, double b, int* Error);
