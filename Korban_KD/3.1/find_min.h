typedef double (*dndFUNC)(double x);
#define MAX_IT 1e16
#define NUM 1e5

enum FIND_ROOT_CODES
{
    NOT_UNIMODAL = -2,
    NOT_FOUND,
};




int find_min(dndFUNC f, double a, double b, double eps, double *x);


