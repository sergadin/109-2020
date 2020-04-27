#include <stdio.h>
#include <stdlib.h>

#include "../lib/ustrings.h"
#include "determinant.h"

void free_1d_matrix(char **matrix, int order) {
	for (int i = 0; i < order * order; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
