typedef double (*dFUNC)(double x);
typedef double (*diFUNC)(double x, int n);
typedef enum {
	OK,
	TOO_LONG,
	BAD_VALUE
} Status;
typedef double (*taylorFUNC)(double x, double precision, int *n, Status *s);

double taylor_recurrent(double x, double precision, int *n, Status *s, dFUNC start_value, diFUNC recurrence);
double taylor_exp(double x, double precision, int *n, Status *s);
double taylor_sin(double x, double precision, int *n, Status *s);
double taylor_cos(double x, double precision, int *n, Status *s);
double taylor_log(double x, double precision, int *n, Status *s);

double one(double x);
double linear(double x, int n);

double id(double x);
double sin_square(double x, int n);

double cos_square(double x, int n);
