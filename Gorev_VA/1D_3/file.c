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

double *multiply(double *matr, int m, int n, int i1, double c);
double *multiply(double *matr, int m, int n, int i1, double c)
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

double *plus_str(double *matr, int m, int n, int i1, int i2, double c);
double *plus_str(double *matr, int m, int n, int i1, int i2, double c)
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

void diag(double *A, double *A_dop, int n, int *Error);
void diag(double *A, double *A_dop, int n, int *Error)
{
	double *B, *B_dop;
	if (n > 1)
	{
		*Error = 1;
		for (int i = 0; i < n; i++)
		{
			if (Abs(A[i * n]) >= eps)
			{
				*Error = 0;
				A = swap(A, n, n, 0, i);
				A_dop = swap(A, n, n, 0, i);
				break;
			}
		}
		print_matrix(A, n, n);
		printf("\n");
		if (*Error == 0)
		{
			for (int i = 1; i < n; i++)
				for (int j = 0; j < n; j++)
				{
					A = plus_str(A, n, n, i, 0, -A[i * n] / A[0]);
					A_dop = plus_str(A_dop, n, n, i, 0, -A[i * n] / A[0]);
				}
			print_matrix(A, n, n);
			printf("\n");
			B = (double*)malloc((n - 1) * (n - 1) * sizeof(double));
			B_dop = (double*)malloc((n - 1) * (n - 1) * sizeof(double));
			for (int i = 0; i < (n - 1); i++)
				for (int j = 0; j < (n - 1); j++)
				{
					B[i * (n - 1) + j] = A[(i + 1) * n + (j + 1)];
					B_dop[i * (n - 1) + j] = A_dop[(i + 1) * n + (j + 1)];
				}
			diag(B, B_dop, n - 1, Error);
			if (*Error == 0)
				for (int i = 0; i < (n - 1); i++)
					for (int j = 0; j < (n - 1); j++)
					{
						A[(i + 1) * n + (j + 1)] = B[i * (n - 1) + j];
						A_dop[(i + 1) * n + (j + 1)] = B_dop[i * (n - 1) + j];
					}
			print_matrix(A, n, n);
			printf("\n");
		}
	}
}

double *inverse(double *A, int n, int *Error);
double *inverse(double *A, int n, int *Error)
{
	double *B;
	B = (double*)malloc(n * n * sizeof(double));

}

int main(void)
{
	double *matr, *MATR;
	int N = 3, M = 3;
	int *Error;
	Error = (int*)malloc(sizeof(int));

	matr = (double*)malloc(N * M * sizeof(double));
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			matr[i * N + j] = i * N + j;
	MATR = multiply(matr, M, N, 0, 2.0);

	print_matrix(matr, M, N);
	printf("\n");

	diag(matr, MATR, N, Error);

	/*print_matrix(matr, M, N);
	printf("\n");
	diag(matr, MATR, N, Error);
	print_matrix(MATR, M, N);*/

	free(matr);
	free(MATR);
	free(Error);
	return 0;
}
