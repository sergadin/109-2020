#include "libs.h"

double deter(int n, double **matrix_now) {
    double **matrix = malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(double) * n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = matrix_now[i][j];
        }
    }
    double eps = 0.00001;
    double det = 1;
    for (int k = 0; k < n; k++) {
        for (int i = k; i < n; i++) {
            double tmp = matrix[i][k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n; j++)
                matrix[i][j] = matrix[i][j] / tmp;
            det *= tmp;
            if (i == k) continue;
            for (int j = 0; j < n; j++)
                matrix[i][j] = matrix[i][j] -matrix[k][j];
        }
    }
    for (int i = 0; i < n; i++)
        det *= matrix[i][i];
    
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    
    return det;
}


void reverse(int n, double **matrix_now, double **new) {
    double **matrix = malloc(sizeof(double *) * n);
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(sizeof(double) * n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = matrix_now[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                new[i][j] = 1;
            }
        }
    }
    const double eps = 0.000001;
    for (int k = 0; k < n; k++) {
        for (int i = k; i < n; i++) {
            double tmp = matrix[i][k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n; j++) {
                matrix[i][j] = matrix[i][j] / tmp;
                new[i][j] = new[i][j] / tmp;
            }
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                matrix[i][j] = matrix[i][j] - matrix[k][j];
                new[i][j] = new[i][j] - new[k][j];
            }
        }
    }
    for (int k = n - 1; k >= 0; k--) {
        for (int i = n - 1; i >= 0; i--) {
            double tmp = matrix[i][k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n; j++) {
                matrix[i][j] = matrix[i][j] / tmp;
                new[i][j] = new[i][j] / tmp;
            }
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                matrix[i][j] = matrix[i][j] - matrix[k][j];
                new[i][j] = new[i][j] - new[k][j];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
