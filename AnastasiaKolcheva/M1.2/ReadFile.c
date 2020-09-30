#include <stdio.h>
#include "matrix.h"
#include "error.h"

void main(void)
{
	matrix_t* matrix;
	double det;
	int error = readMatrix("matrix.txt", &matrix);
	if (error == S_OK)
	{
		printMatrix(matrix);
		printf("Rank of Matrix: %d\n", getRank(matrix));
		if (getDeterminant(matrix, &det) == S_OK)
		{
			printf("Determinant = %lg\n", det);
		}
		freeMatrix(matrix);
		printf("%s (%d)\n", getErrorMessage(error), error);
	}
	else
	{
		printf("error - %s (%d)\n", getErrorMessage(error), error);
	}
}