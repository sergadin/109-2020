#include <math.h>
#include "help.h"

#define eps 1e-7

double root(point_on_function f, point_on_function f_fpr, point_on_function f_spr, double a, double b, char *check){
    double x_n;
    double x_n_plus_one;
    double inaccuracy = 1;
    if ((*f)(a)*(*f_spr)(a) > 0)
        x_n = a;
    else {
        if ((*f)(b) * (*f_spr)(b) > 0)
            x_n = b;
        else {
            *check = 0;
            return 0;
        };
    }

    while (fabs(inaccuracy) >= eps) {
        x_n_plus_one = next_point(f, f_fpr, x_n);
        inaccuracy = x_n_plus_one - x_n;
        x_n = x_n_plus_one;
    }

    return x_n_plus_one;
}
