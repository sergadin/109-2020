#include "libs.h"

double deter(int n, double *matrix_now) {
    double *matrix = malloc(sizeof(double *) * n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i*n + j] = matrix_now[i*n + j];
        }
    }
    double eps = 0.00001;
    double det = 1;
    for (int k = 0; k < n; k++) {
        for (int i = k; i < n; i++) {
            double tmp = matrix[i*n + k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n; j++)
                matrix[i*n + j] = matrix[i*n + j] / tmp;
            det *= tmp;
            if (i == k) continue;
            for (int j = 0; j < n; j++)
                matrix[i*n + j] = matrix[i*n + j] - matrix[k*n + j];
        }
    }
    for (int i = 0; i < n; i++)
        det *= matrix[i*n + i];
    
    free(matrix);
    
    return det;
}


void reverse(int n, double *matrix_now, double *new) {
    double *matrix = malloc(sizeof(double *) * n * n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i*n + j] = matrix_now[i*n + j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                new[i*n + j] = 1;
            } else {
                new[i*n + j] = 0;
            }
        }
    }
    const double eps = 0.000001;
    for (int k = 0; k < n; k++) {
        for (int i = k; i < n; i++) {
            double tmp = matrix[i*n + k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n; j++) {
                matrix[i*n + j] = matrix[i*n + j] / tmp;
                new[i*n + j] = new[i*n + j] / tmp;
            }
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                matrix[i*n + j] = matrix[i*n + j] - matrix[k*n + j];
                new[i*n + j] = new[i*n + j] - new[k*n + j];
            }
        }
    }
    for (int k = n - 1; k >= 0; k--) {
        for (int i = n - 1; i >= 0; i--) {
            double tmp = matrix[i*n + k];
            if (fabs(tmp) < eps) continue;
            for (int j = 0; j < n; j++) {
                matrix[i*n + j] = matrix[i*n + j] / tmp;
                new[i*n + j] = new[i*n + j] / tmp;
            }
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                matrix[i*n + j] = matrix[i*n + j] - matrix[k*n + j];
                new[i*n + j] = new[i*n + j] - new[k*n + j];
            }
        }
    }
    free(matrix);
}
