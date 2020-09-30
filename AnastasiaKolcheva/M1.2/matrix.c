#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "error.h"

int readMatrix(const char* fileName, matrix_t** matrix)
{
	int rows, columns, row, column;
	matrix_t* result;

	if (fileName == NULL)
	{
		return E_INVALIDFILE;
	}
	if (matrix == NULL)
	{
		return E_NULLREFERENCE;
	}
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		return E_CANNOTOPENFILE;
	}

	fscanf(file, "%d %d\n", &rows, &columns);

	if (rows <= 0 || columns <= 0)
	{
		return E_OUTOFRANGE;
	}

	result = (matrix_t*)malloc(sizeof(matrix_t));
	if (result == NULL)
	{
		return E_OUTOFMEMORY;
	}

	result->rows = rows;
	result->columns = columns;
	result->values = (double*)malloc(rows * columns * sizeof(double));
	if (result->values == NULL)
	{
		free(result);
		return E_OUTOFMEMORY;
	}

	for (row = 0; row < rows; ++row)
	{
		for (column = 0; column < columns; ++column)
		{
			fscanf(file, "%lg", &result->values[row * columns + column]);
		}
	}

	fclose(file);
	*matrix = result;
	return S_OK;
}

int printMatrix(const matrix_t* matrix)
{
	if (matrix == NULL)
	{
		return E_NULLREFERENCE;
	}
	int count, index;
	if (matrix == NULL)
	{
		return -1;
	}
	count = matrix->rows * matrix->columns;
	printf("rows: %d, columns: %d\n", matrix->rows, matrix->columns);
	for (index = 0; index < count; ++index)
	{
		printf("%5lg ", matrix->values[index]);
		if (index % matrix->columns == matrix->columns - 1)
		{
			printf("\n");
		}
	}
	return S_OK;
}

int freeMatrix(matrix_t* matrix)
{
	if (matrix != NULL)
	{
		free(matrix->values);
		free(matrix);
		return S_OK;
	}
	return E_NULLREFERENCE;
}

void gaussElimination(int rows, int columns, double* matrix);
int getNonZeroRows(matrix_t* matrix);


int getRank(matrix_t* matrix)
{
	gaussElimination(matrix->rows, matrix->columns, matrix->values);
	return getNonZeroRows(matrix);
}

void gaussElimination(int rows, int columns, double* matrix)
{
	int i, col, row;
	double term;
	for (i = 0; i < rows - 1; i++) {
		for (row = i + 1; row < rows; row++) {
			term = matrix[row * columns + i] / matrix[i * columns + i];
			for (col = 0; col < columns; col++) {
				matrix[row * columns + col] = matrix[row * columns + col] - term * matrix[i * columns + col];
			}
		}
	}
}

#define EPSILON 1E-16

int zeroRow(int row, matrix_t* matrix)
{
	int index = row * matrix->columns;
	for (int col = 0; col < matrix->columns; ++col)
	{
		if (fabs(matrix->values[index + col]) > EPSILON)
		{
			return 0;
		}
	}
	return 1;
}

int getNonZeroRows(matrix_t* matrix)
{
	int row;
	int rank = matrix->rows > matrix->columns ? matrix->columns : matrix->rows;
	for (row = 0; row < matrix->rows; ++row)
	{
		if (zeroRow(row, matrix))
		{
			--rank;
		}
	}
	return rank;
}


int getDeterminant(matrix_t* matrix, double* result)
{
	double value = 1.0;
	int size, index, rank;
	if (matrix->columns != matrix->rows)
	{
		return E_INVALIDARG;
	}
	size = matrix->columns;
	gaussElimination(size, size, matrix->values);
	rank = getNonZeroRows(matrix);
	if (rank == size)
	{
		value = 1;
		for (index = 0; index < size; ++index)
		{
			value *= matrix->values[index * size + index];
		}
		*result = value;
	}
	else
	{
		*result = 0;
	}
	return S_OK;
}

