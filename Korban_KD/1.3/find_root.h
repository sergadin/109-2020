typedef double (*dndFUNC)(double x);
#define MAX_IT 1e16
#define PRECITION 1e-16

enum FIND_ROOT_CODES
{
	NO_ROOT = -3,
    NOT_FOUND,
    UNABLE,
};



int find_root(dndFUNC f, double a, double b, double eps, double *x);


