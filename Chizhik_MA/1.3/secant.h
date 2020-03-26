typedef double (*dFUNC)(double x);

void display_amount_of_iterations(int a);
double find_root(dFUNC fn, double a, double b, double precision);
