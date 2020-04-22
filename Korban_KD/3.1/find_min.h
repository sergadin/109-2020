typedef double (*dndFUNC)(double x);

enum FIND_ROOT_CODES
{
    NOT_UNIMODAL = -3,
    NOT_FOUND,
    DIVISION_BY_ZERO
};




int find_min(dndFUNC f, double a, double b, double eps, double *x);


