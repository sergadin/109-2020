#include <math.h>
#include "../lib/umath.h"
#include "determinant.h"

double find_determinant(double *matrix, int n, double precision) {
	double det = 1, sign = 1;
	int str_of_max;

	for (int j = 0; j < n - 1; j++) {
		str_of_max = j;
		for (int i = j; i < n; i++) {
			if (fabs(*get_matrix_element(matrix, n, i, j)) > 
			    fabs(*get_matrix_element(matrix, n, str_of_max, j))) {
				str_of_max = i;
			}
		}
		if (compareDoubles(*get_matrix_element(matrix, n, str_of_max, j), 0, precision) == 0) {
			return 0;
		}

		if (str_of_max != j) {
			for (int a = 0; a < n; a++) {
				swap(get_matrix_element(matrix, n, j, a), 
				     get_matrix_element(matrix, n, str_of_max, a));
			}
			sign *= -1;
		}

		for (int b = j + 1; b < n; b++) {
			double coef = *get_matrix_element(matrix, n, b, j) / *get_matrix_element(matrix, n, j, j);
			for (int c = j; c < n; c++) {
				*get_matrix_element(matrix, n, b, c) -= coef * *get_matrix_element(matrix, n, j, c);
			}
		}
	}

	for (int k = 0; k < n; k++) {
		det *= *get_matrix_element(matrix, n, k, k);
	}

	return sign * det;
}

double *get_matrix_element(double *matrix, int order, int i, int j) {
	unsigned int something_went_wrong = (i > order) || (j > order) || (i < 0) || (j < 0);
	if (something_went_wrong) {
		return 0;
	}
	return &matrix[i * order + j];
}
