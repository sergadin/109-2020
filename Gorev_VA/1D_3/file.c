#include <stdio.h>
#include <stdlib.h>

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

double *transp(double *matr, int m, int n);
double *transp(double *matr, int m, int n)
{
	double *T;
	T = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			T[i * m + j] = matr[j * n + i];
	return T;
}

double *swap(double *matr, int m, int n, int i1, int i2);
double *swap(double *matr, int m, int n, int i1, int i2)
{
	double *A;
	if (i1 == i2)
		return matr;
	if (i1 > i2)
	{
		A = (double*)malloc(sizeof(double));
		A[0] = i1;
		i1 = i2;
		i2 = A[0];
		free(A);
	}
	A = (double*)malloc(m * n * sizeof(double));

	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i1 * n + j] = matr[i2 * n + j];
	for (int i = i1 + 1; i < i2; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i2 * n + j] = matr[i1 * n + j];
	for (int i = i2 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];

	return A;
}

double multiply(double *matr, int m, int n, int i1, double c);
double multiply(double *matr, int m, int n, int i1, double c)
{
	double *A;
	A = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i1 * n + j] = c * matr[i1 * n + j];
	for (int i = i1 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	return A;
}

double plus_str(double *matr, int m, int n, int i1, int i2, double c);
double plus_str(double *matr, int m, int n, int i1, int i2, double c)
{
	double *A;
	A = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < i1; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	for (int j = 0; j < n; j++)
		A[i1 * n + j] = matr[i1 * n + j] + c * matr[i2 * n + j];
	for (int i = i1 + 1; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = matr[i * n + j];
	return A;
}

double *inverse(double *A, int n)
{
	double *B;
	B = (double*)malloc(n * n * sizeof(double));

}

int main(void)
{
	double *matr, *MATR;
	int N = 2, M = 3;
	matr = (double*)malloc(N * M * sizeof(double));
	matr[0] = 0, matr[1] = 1, matr[2] = 2, matr[3] = 3, matr[4] = 4, matr[5] = 5;
	MATR = multiply(matr, M, N, 0, 2.0);
	print_matrix(matr, M, N);
	printf("\n");
	print_matrix(MATR, M, N);

	MATR = plus_str(matr, M, N, 1, 0, 2.0);
	printf("\n");
	print_matrix(MATR, M, N);

	
	return 0;
}
