typedef double (*dndFUNC)(double x);


double part_sum(dndFUNC f, double a, double b); 
double gaus(dndFUNC f, double a, double b, int n);
int integrate(dndFUNC f, double , double b,  double eps, double *x);
