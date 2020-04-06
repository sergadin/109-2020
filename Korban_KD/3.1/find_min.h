typedef double (*dndFUNC)(double x);
#define MAX_IT 1e16
#define PRECITION 1e-16
#define NUM 1e4
#define NOT_FOUND (-1)



int find_min(dndFUNC f, double a, double b, double eps, double *x);


