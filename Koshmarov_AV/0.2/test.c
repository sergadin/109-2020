#include <stdio.h>
#include <stdlib.h>
#include "help.h"

#define eps 1e-7
#define al 4
#define cp 3

double zero(double x, double y){
    return 0*x + 0*y;
}

double line(double x, double y){
    return x + y;
}

double square(double x, double y){
    return x*y + 2;
}

double d_square(double x, double y){
    return x*x + x*y + y*y + 10;
}

int main(){

    pointer_on_func mas_func[al] = {zero, line, square, d_square};
    double pointers_x[cp] = {0.75, 0, 5};
    double pointers_y[cp] = {0.75, 0, 5};
    double check_mac[cp][al] = {0, 1.5, 2.5625, 11.6875, 0, 0, 2, 10, 0, 10, 27, 85};
    double *po_mas = (double*) malloc(sizeof(double )*cp);

    for (int i = 0; i < al; i++){
        result(*mas_func[i], po_mas, pointers_x, pointers_y, cp);
        printf("Test for %d function:\n", i + 1);
        for (int j = 0; j < cp; j ++) {
            printf("%f", po_mas[j]);
            if(abs(po_mas[j] - check_mac[j][i]) <= eps)
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
