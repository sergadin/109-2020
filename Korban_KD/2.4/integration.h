typedef double (*dndFUNC)(double x);
#define NUMBER 4
#define STEP 2
#define MAX_IT 1e10

double part_sum(dndFUNC f, double a, double b); 
double gaus(dndFUNC f, double a, double b, int n);
int integrate(dndFUNC f, double , double b,  double eps, double *x);
