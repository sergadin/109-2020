typedef double (*dFUNC)(double x);
typedef enum {
	OK,
	NOT_UNIMODAL
} Status;

double find_minimum(dFUNC f, double a, double b, double precision, Status *s);
double find_parabola_vertex(double *x, double *y);
