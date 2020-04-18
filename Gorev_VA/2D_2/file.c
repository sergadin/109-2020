#include <stdio.h>
#include <stdlib.h>
#define eps 0.0000001

double Abs(double x);
double Abs(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

double **centr_sym(double **matr, int n);
double **centr_sym(double **matr, int n)
{
	double **T;
	T = (double**)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		T[i] = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T[i][j] = matr[n - 1 - i][n - 1 - j];
	return T;
}

double **swap(double **matr, int m, int n, int i1, int i2);
double **swap(double **matr, int m, int n, int i1, int i2)
{
	double **A;
	if (i1 == i2)
		return matr;
	if (i1 > i2)
	{
		A = (double**)malloc(sizeof(double));
		A[0] = (double*)malloc(sizeof(double));
		A[0][0] = i1;
		i1 = i2;
		i2 = A[0][0];
		free(A[0]);
		free(A);
	}
	A = (double**)malloc(m * sizeof(double));
	for (int i = 0; i < m; i++)
		A[i] = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];
	for (int j = 0; j < n; j++)
		A[i1][j] = matr[i2][j];
	for (int i = i1 + 1; i < i2; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];
	for (int j = 0; j < n; j++)
		A[i2][j] = matr[i1][j];
	for (int i = i2 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];

	return A;
}

double **multiply(double **matr, int m, int n, int i1, double c);
double **multiply(double **matr, int m, int n, int i1, double c)
{
	double **A;
	A = (double**)malloc(m * sizeof(double));
	for (int i = 0; i < m; i++)
		A[i] = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];
	for (int j = 0; j < n; j++)
		A[i1][j] = c * matr[i1][j];
	for (int i = i1 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];
	return A;
}

double **plus_str(double **matr, int m, int n, int i1, int i2, double c);
double **plus_str(double **matr, int m, int n, int i1, int i2, double c)
{
	double **A;
	A = (double**)malloc(m * sizeof(double));
	for (int i = 0; i < m; i++)
		A[i] = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];
	for (int j = 0; j < n; j++)
		A[i1][j] = matr[i1][j] + c * matr[i2][j];
	for (int i = i1 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = matr[i][j];
	return A;
}

double det(double **A, int n);
double det(double **A, int n)
{
	int q = 0;
	double det = 1.0;
	for (int k = 0; k < (n - 1); k++)
	{
		q = 1;
		for (int i = k; i < n; i++)
		{
			if (Abs(A[i][k]) >= eps)
			{
				q = 0;
				A = swap(A, n, n, k, i);
				break;
			}
		}
		if (q == 0)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					A = plus_str(A, n, n, i, k, -A[i][k] / A[k][k]);
				}
		}
		else
			return 0.0;
	}
	for (int k = 0; k < n; k++)
		det *= A[k][k];
	return det;
}

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

int main(void)
{
	double **matr;
	int N = 3, M = 3;
	matr = (double**)malloc(M * sizeof(double));
	for (int i = 0; i < M; i++)
		matr[i] = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			matr[i][j] = i * N + j;

	print_matrix(matr, M, N);
	printf("\n");

	printf("%g\n", det(matr, N));
	printf("\n");

	for (int i = 0; i < M; i++)
		free(matr[i]);
	free(matr);
	return 0;
}
