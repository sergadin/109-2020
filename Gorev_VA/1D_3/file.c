#include <stdio.h>
#include <stdlib.h>
#include "inverse.h"

void print_matrix(double *matr, int m, int n);
void print_matrix(double *matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%g ", matr[i * n + j]);
		printf("\n");
	}
}

double *read_matrix(int m, int n);
double *read_matrix(int m, int n)
{
	double *matr;
	matr = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			matr[i * n + j];
	return matr;
}

int main(void)
{
	double *matr, *MATR;
	int N = 3, M = 3;
	int *Error;
	Error = (int*)malloc(sizeof(int));

	matr = (double*)malloc(N * M * sizeof(double));
	matr[0] = matr[1] = matr[2] = matr[3] = matr[4] = matr[6] = 1;
	matr[5] = matr[7] = matr[8] = 0;
	MATR = multiply(matr, M, N, 0, 2.0);

	print_matrix(matr, M, N);
	printf("\n");

	print_matrix(inverse(matr, N, Error), M, N);

	/*print_matrix(matr, M, N);
	printf("\n");
	diag(matr, MATR, N, Error);
	print_matrix(MATR, M, N);*/

	free(matr);
	free(MATR);
	free(Error);
	return 0;
}