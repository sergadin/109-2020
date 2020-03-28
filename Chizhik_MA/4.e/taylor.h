typedef double (*dFUNC)(double x);
typedef enum {
	OK,
	TOO_LONG
} Status;
typedef double (*taylorFUNC)(double x, double precision, int *n, Status *s);

double taylor_exp(double x, double precision, int *n, Status *s);
double taylor_sin(double x, double precision, int *n, Status *s);
double taylor_cos(double x, double precision, int *n, Status *s);
double taylor_log(double x, double precision, int *n, Status *s);
