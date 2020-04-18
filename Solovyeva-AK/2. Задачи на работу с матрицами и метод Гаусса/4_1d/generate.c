#include "libs.h"

void print_matrix(int n, double *matrix) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%.2lf ", matrix[i*(n + 1) + j]);
        }
        printf("\n");
    }
    return;
}


int main() {
    int n = 5;
    double *matrix = malloc(n * (n + 1) * sizeof(*matrix));
    double *x = malloc(n * sizeof(*x));
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n+1; j++) {
            if (j == n) {
                matrix[i*(n + 1) + j] = 4*i + 1;
            } else if ( i != j) {
                matrix[i*(n + 1) + j] = (double)(i + j) / 5;
            } else { 
                matrix[i*(n + 1) + j] = 40 + 10 + (double)j / 10 + (double)i / 4;
            }
        }
    }
    
    print_matrix(n, matrix);
    gauss_m(n, matrix, x);
    for(int i = 0; i < n; i++) {
        printf("%.8lf ", x[i]);
    }
    
    return 0;
}

