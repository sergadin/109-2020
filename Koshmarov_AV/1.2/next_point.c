#include "help.h"

double next_point(point_on_function f, point_on_function f_fpr, double x ){
    double point;
    point = - ((*f)(x)/(*f_fpr)(x)) + x;
    return point;
}

