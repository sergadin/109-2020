#include "libs.h"

void solve_system(int n, double **matrix, double *x) {
    double max_elem;
    int max_index;
    const double eps = 0.000001;
    for (int k = 0; k < n; k++) {
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

        for (int j = 0; j < n + 1; j++) {
            double tmp = matrix[k][j];
            matrix[k][j] = matrix[max_index][j];
            matrix[max_index][j] = tmp;
        }

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
}
