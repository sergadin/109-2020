#ifndef __MATRIX_H___

#define __MATRIX_H___

typedef struct _matrix_t
{
	int rows;
	int columns;
	double* values;
} matrix_t;

int readMatrix(const char* fileName, matrix_t** matrix);

int freeMatrix(matrix_t* matrix);

int printMatrix(const matrix_t* matrix);

int getRank(matrix_t* matrix);

int getDeterminant(matrix_t* matrix, double* result);

#endif