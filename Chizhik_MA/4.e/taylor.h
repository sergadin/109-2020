typedef double (*dFUNC)(double x);
typedef enum {
	OK,
	TOO_LONG
} Status;

double taylor_exp(double x, double precision, int *n, Status *s);
