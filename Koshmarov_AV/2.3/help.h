typedef double (*point_on_function)(double x);

double simpson(point_on_function f, double a, double b, int n, int *buff_err);