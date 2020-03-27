typedef double (*dFUNC)(double x);
typedef enum {
	OK,
	METHOD_DOES_NOT_CONVERGE
} Status;

double integration_with_fixed_step(dFUNC f, double a, double b, int n);
double simpson_integral(dFUNC f, double a, double b, double precision, Status *s);
