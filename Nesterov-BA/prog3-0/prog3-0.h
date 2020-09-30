typedef int (*fpointer)(int n, double x);
#define eps 0.000001

int fold(fpointer f, double *x, int n, int m);
