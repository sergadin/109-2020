#include <math.h>
#include "../lib/umath.h"
#include "determinant.h"

#define matrix(n, i, j) matrix[(i) * (n) + (j)]

double find_determinant(double *matrix, int n, double precision) {
	double det = 1, sign = 1;
	int str_of_max;

	for (int j = 0; j < n; j++) {
		str_of_max = j;
		for (int i = j + 1; i < n; i++) {
			if (fabs(matrix(n, i, j)) > 
			    fabs(matrix(n, str_of_max, j))) {
				str_of_max = i;
			}
		}
		if (compareDoubles(matrix(n, str_of_max, j), 0, precision) == 0) {
			return 0;
		}

		if (str_of_max != j) {
			for (int a = 0; a < n; a++) {
				swap(&(matrix(n, j, a)), &(matrix(n, str_of_max, a)));
			}
			sign *= -1;
		}

		for (int b = j + 1; b < n; b++) {
			double coef = matrix(n, b, j) / matrix(n, j, j);
			for (int c = j; c < n; c++) {
				matrix(n, b, c) -= coef * matrix(n, j, c);
			}
		}

		det *= matrix(n, j, j);
	}

	return sign * det;
}
