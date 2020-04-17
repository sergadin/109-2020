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
	B = A, B_dop = A_dop;
	for (int k = 0; k < (n - 1); k++)
	{
		*Error = 1;
		for (int i = k; i < n; i++)
		{
			if (Abs(A[i * n + k]) >= eps)
			{
				*Error = 0;
				A = swap(A, n, n, k, i);
				A_dop = swap(A_dop, n, n, k, i);

				A = multiply(A, n, n, k, 1.0 / A[k * n + k]);
				A_dop = multiply(A_dop, n, n, k, 1.0 / A[k * n + k]);
				break;
			}
		}
		print_matrix(A, n, n);
		printf("\n");
		if (*Error == 0)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					A = plus_str(A, n, n, i, k, -A[i * n + k] / A[k * n + k]);
					A_dop = plus_str(A_dop, n, n, i, k, -A[i * n + k] / A[k * n + k]);
				}
		}
		else
			break;
		print_matrix(A, n, n);
		printf("\n");
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			B[i * n + j] = A[i * n + j];
			B_dop[i * n + j] = A_dop[i * n + j];
		}
}

double *inverse(double *A, int n, int *Error);
double *inverse(double *A, int n, int *Error)
{
	double *B;
	B = (double*)malloc(n * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				B[i * n + j] = 1;
			else
				B[i * n + j] = 0;
	diag(A, B, n, Error);
	if (*Error == 1)
		return A;
	A = transp(A, n, n);
	B = transp(B, n, n);
	diag(A, B, n, Error);
	return transp(B, n, n);
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
	matr[8] += 1.0;
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
