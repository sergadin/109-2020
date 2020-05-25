#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "find.h"
#define eps 0.0001

int main(void) {
    double a, integral;
    scanf("%lf", &a);
    integral = find_root(a, eps);
    if(integral < 0) 
        printf("У уравнения нет корней\n");
    else
        printf("%lf\n", integral);
    return 0;
}
