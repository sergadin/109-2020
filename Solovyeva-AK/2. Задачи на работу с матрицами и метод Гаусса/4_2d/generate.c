#include "libs.h"

int main() {
    int n = 5;
    double **matrix = malloc(n * sizeof(*matrix));
    double *x = malloc(n * sizeof(*x));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * (n + 1));
    }
    
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n+1; j++) {
            if (j == n) {
                matrix[i][j] = 4*i + 1;
            } else if ( i == j) {
                matrix[i][j] = (double)(i + j) / 5;
            } else { 
                matrix[i][j] = 40 + 10 + (double)j / 10 + (double)i / 4;
            }
        }
    }
    
    print_system(n, matrix);
    solve_system(n, matrix, x);
    printf("\nSolution:\n\n");
    for(int i = 0; i < n; i++) {
        printf("x%d=%.8lf\n", i, x[i]);
    }
    if(check_solution(n, matrix, x)){
        printf("\nCorrect\n");
    } else {
        printf("\nIncorrect\n");
    }
    
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(x);
    
    return 0;
}

