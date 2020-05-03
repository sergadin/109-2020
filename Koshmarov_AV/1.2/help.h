typedef double (*point_on_function)(double x);

double next_point(point_on_function f, point_on_function f_fpr, double x ); //ищет следующую точку
double root(point_on_function f, point_on_function f_fpr, point_on_function f_spr, double a, double b, char *check); //ищет корень
