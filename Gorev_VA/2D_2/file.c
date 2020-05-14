#include <stdio.h>
#include <stdlib.h>
#include "det.h"

void print_matrix(double **matr, int m, int n);
void print_matrix(double **matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%g ", matr[i][j]);
		printf("\n");
	}
} 

double **Identity(int n);
double **Identity(int n)
{
	double **E;
	E = (double**)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		E[i] = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				E[i][j] = 1;
			else
				E[i][j] = 0;
	return E;
}

double **M1(int n);
double **M1(int n)
{
	double **M;
	M = (double**)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		M[i] = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			M[i][j] = i * n + j;
	return M;
}

double **M2(int n);
double **M2(int n)
{
	double **M;
	M = (double**)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		M[i] = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		M[i][0] = 1;
		for (int j = 1; j < n; j++)
			M[i][j] = M[i][j - 1] * i;
	}
		
	return M;
}

int main(void)
{
	double **matr;
	int N = 4;

	matr = Identity(N);
	printf("A =\n");
	print_matrix(matr, N, N);
	printf("\n");
	printf("|A| = %g\n", det(matr, N));
	printf("\n");

	matr = M1(N);
	printf("A =\n");
		print_matrix(matr, N, N);
	printf("\n");
	printf("|A| = %g\n", det(matr, N));
	printf("\n");

	matr = M2(N);
	printf("A =\n");
		print_matrix(matr, N, N);
	printf("\n");
	printf("|A| = %g\n", det(matr, N));
	printf("\n");

	for (int i = 0; i < N; i++)
		free(matr[i]);
	free(matr);
	return 0;
}