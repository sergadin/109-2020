typedef double (*dFUNC)(double x);
typedef enum {
        OK,
        NO_ROOTS,
        SAME_SIGN_AT_THE_ENDPOINTS
} Status;


void display_amount_of_iterations(int a);
double find_root(dFUNC fn, double a, double b, double precision, Status *s);
