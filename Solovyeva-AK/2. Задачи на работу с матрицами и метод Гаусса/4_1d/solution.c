#include "libs.h"

void gauss_m(int n, double *matrix_now, double *x) {
    double *matrix = malloc(sizeof(double *) * n * (n+1));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            matrix[i*(n + 1) + j] = matrix_now[i*(n + 1) + j];
        }
    }
    double max_elem;
    int max_index;
    const double eps = 0.000001;
    for (int k = 0; k < n; k++) {
        max_elem = fabs(matrix[k*(n + 1) + k]);
        max_index = k;
        for (int i = k + 1; i < n; i++) {
            if (max_elem < fabs(matrix[i*(n + 1) + k])) {
                max_elem = fabs(matrix[i*(n + 1) + k]);
                max_index = i;
            }
        }
        if (max_elem < eps) {
            return;
        }

        for (int j = 0; j < n + 1; j++) {
            double tmp = matrix[k*(n + 1) + j];
            matrix[k*(n + 1) + j] = matrix[max_index*(n + 1) + j];
            matrix[max_index*(n + 1) + j] = tmp;
        }

        for (int i = k; i < n; i++) {
            double tmp = matrix[i*(n + 1) + k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n + 1; j++)
            matrix[i*(n + 1) + j] = matrix[i*(n + 1) + j] / tmp;
            if (i == k) continue;
            for (int j = 0; j < n + 1; j++)
            matrix[i*(n + 1) + j] = matrix[i*(n + 1) + j] - matrix[k*(n + 1) + j];
        }
    }

    for (int k = n - 1; k >= 0; k--) {
        x[k] = matrix[k*(n + 1) + n];
        for (int i = 0; i < k; i++)
        matrix[i*(n + 1) + n] = matrix[i*(n + 1) + n] - matrix[i*(n + 1) + k] * x[k];
    }
    free(matrix);
}
