#include <stdio.h>
#include <stdlib.h>
№include <math.h>
#include "help.h"

#define eps 1e-7
#define al 4
#define cp 3

double zero(double x){
    return 0*x;
}

double line(double x){
    return x + 1;
}

double square(double x){
    return x*x + 2;
}

double cube(double x){
    return x*x*x + 3;
}

int main(){

    pointer_on_func mas_func[al] = {zero, line, square, cube};
    double pointers[cp] = {1.15, 0, 15};
    double check_mac[cp][al] = {0, 2.15, 3.3225, 4.520875, 0, 1, 2, 3, 0, 16, 227, 3378};
    double *po_mas = (double*) malloc(sizeof(double )*cp);

    for (int i = 0; i < al; i++){
        result(*mas_func[i], po_mas, pointers, cp);
        printf("Test for %d function:\n", i + 1);
        for (int j = 0; j < cp; j ++) {
            if(fabs(po_mas[j] - check_mac[j][i]) <= eps)
                printf("    %d.Test completed\n", j + 1);
            else {
                printf("    %d.Test not completed!\n", j + 1);
                printf("Check your program!\n");
                return 0;
            }
        }
    }

    printf("\n");
    printf("Your program is good!\n");
    free(po_mas);
    return 0;
}
