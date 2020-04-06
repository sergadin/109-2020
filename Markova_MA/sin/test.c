#include "f.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double x = 1, eps = 0.0001;
    printf("%lf %lf \n", x, eps);
    printf("%lf \n", sin_(x, eps));
}
