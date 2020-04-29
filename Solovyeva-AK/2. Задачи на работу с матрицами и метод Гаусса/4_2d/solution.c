#include "libs.h"



double max_2_dbl (double x, double y){
	if (x < y) {
		return y;
	} else {
		return x;
	}
}

double max_3_dbl (double x, double y, double z) {
	return max_2_dbl(max_2_dbl(x,y), z); 
}

int compare(double x, double y, double eps) {
	if (fabs(x-y) < (eps* max_3_dbl(x, y, 1))) {
		return 1;
	} else {
		return 0;
	}
}

int check_solution(int n, double **matrix, double *x) {
    const double eps = 0.000001;
    for (int i = 0; i < n; i++){
        double sum = 0;
        for(int j = 0; j < n; j++){
            sum += matrix[i][j]*x[j];
        }
        if(!compare(sum, matrix[i][n], eps)){
            return 0;
        }
    }
    return 1;
}

void print_system(int n, double **matrix) {
    printf("System:\n\n");
    for (int i = 0; i < n; i++) {
        printf("%.2lf*x0", matrix[i][0]);
        for (int j = 1; j < n; j++) {
            printf(" + %.2lf*x%d", matrix[i][j], j);
        }
        printf(" = %.2lf\n", matrix[i][n]);
    }
    return;
}

void solve_system(int n, double **matrix_now, double *x) {
    double **matrix = malloc(n * sizeof(*matrix));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * (n + 1));
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            matrix[i][j] = matrix_now[i][j]; 
        }
    }
    
    const double eps = 0.000001;
    for (int k = 0; k < n; k++) {
        double max_elem;
        int max_index;
        max_elem = fabs(matrix[k][k]);
        max_index = k;
        for (int i = k + 1; i < n; i++)
        if (max_elem < fabs(matrix[i][k])) {
            max_elem = fabs(matrix[i][k]);
            max_index = i;
        }

        if (max_elem < eps) {
            return;
        }
        
        double *index_now = matrix[k];
        matrix[k] = matrix[max_index];
        matrix[max_index] = index_now;
        
        for (int i = k; i < n; i++) {
            double tmp = matrix[i][k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n + 1; j++)
            matrix[i][j] = matrix[i][j] / tmp;
            if (i == k) continue;
            for (int j = 0; j < n + 1; j++)
            matrix[i][j] = matrix[i][j] - matrix[k][j];
        }
    }

    for (int k = n - 1; k >= 0; k--) {
        x[k] = matrix[k][n];
        for (int i = 0; i < k; i++)
        matrix[i][n] = matrix[i][n] - matrix[i][k] * x[k];
    }
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
