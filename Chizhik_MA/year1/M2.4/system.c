#include <stdio.h>

#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "../lib/umath.h"
#include "system.h"

double *solve_system(double **matrix, int n, double precision, Status *s) {
	double *solution;
	*s = OK;
	if ((solution = (double *)malloc(n * sizeof(double))) == NULL) {
		*s = CANNOT_ALLOCATE_MEMORY;
		return NULL;
	}

	for (int j = 0; j < n; j++) {
		int str_of_max = j;
		for (int i = j + 1; i < n; i++) {
			if (fabs(matrix[i][j]) > fabs(matrix[str_of_max][j])) {
				str_of_max = i;
			}
		}
		if (compareDoubles(matrix[str_of_max][j], 0, precision) == 0) {
			*s = NOT_DETERMINED;
			return NULL;
		}

		if (str_of_max != j) {
			for (int a = 0; a < n + 1; a++) {
				swap(&matrix[j][a], &matrix[str_of_max][a]);
			}
		}

		for (int b = j + 1; b < n; b++) {
			double coef = matrix[b][j] / matrix[j][j];
			for (int c = j; c < n + 1; c++) {
				matrix[b][c] -= coef * matrix[j][c];
			}
		}
	}

	for (int j = n - 1; j >= 0; j--) {
		matrix[j][n] /= matrix[j][j];
		matrix[j][j] = 1;

		solution[j] = matrix[j][n];

		for (int k = j - 1; k >= 0; k--) {
			matrix[k][n] -= matrix[k][j] * matrix[j][n];
			matrix[k][j] = 0;
		}
	}

	return solution;
}

void printMatrix(double **matrix, int m, int n, char *comment) {
	fprintf(stdout, "\n%s\n", comment);
	for (int i = 0; i < m; i++) {
               	for (int j = 0; j < n; j++) {
                       	fprintf(stdout, "%lf ", matrix[i][j]);
               	}
               	fprintf(stdout, "\n");
        }
	fprintf(stdout, "\n");
}

void clear_two_dimensional_matrix(double **matrix, int n) {
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
