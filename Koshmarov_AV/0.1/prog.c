#include <stdio.h>
#include "help.h"


double result(pointer_on_func our_func, double point){
    double znach;
    znach = our_func(point);
    return znach;
}
