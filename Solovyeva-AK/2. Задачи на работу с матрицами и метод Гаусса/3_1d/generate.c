#include "libs.h"

void print_matrix(int n, double *matrix) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", matrix[i*n + j]);
        }
        printf("\n");
    }
    return;
}


int main(void){
    FILE *inp;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        return -1;
    }
    int n;
    fscanf (inp, "%d", &n);
    double *matrix = malloc(sizeof(double *) * n * n);
    double *rev = malloc(sizeof(double *) * n * n);
    
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(fscanf(inp, "%lf ", &matrix[i*n + j]) != 1){
                fclose(inp);
                free(matrix);
                free(rev);
                return -1;
            }
        }
    }
    if (deter(n, matrix)) {
        reverse(n, matrix, rev);
        print_matrix(n, rev);
    } else {
        printf("the reverse matrix cannot be found\n");
    }
    free(matrix);
    free(rev);

    fclose(inp);    
    return 0;
}
