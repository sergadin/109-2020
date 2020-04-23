#include <stdlib.h>
#include "inverse.h"

double Abs(double x);
double Abs(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

void centr_sym(double *matr, int n);
void centr_sym(double *matr, int n)
{
	double *T;
	T = (double*)malloc(n * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T[i * n + j] = matr[i * n + j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matr[i * n + j] = T[(n - 1 - i) * n + (n - 1 - j)];
	free(T);
}

void swap(double *matr, int n, int i1, int i2);
void swap(double *matr, int n, int i1, int i2)
{
	for (int j = 0; j < n; j++)
	{
		double A = matr[i1 * n + j];
		matr[i1 * n + j] = matr[i2 * n + j];
		matr[i2 * n + j] = A;
	}
}

void multiply(double *matr, int n, int i1, double c);
void multiply(double *matr, int n, int i1, double c)
{
	for (int j = 0; j < n; j++)
		matr[i1 * n + j] = c * matr[i1 * n + j];
}

void plus_str(double *matr, int n, int i1, int i2, double c);
void plus_str(double *matr, int n, int i1, int i2, double c)
{
	for (int j = 0; j < n; j++)
		matr[i1 * n + j] = matr[i1 * n + j] + c * matr[i2 * n + j];
}

void diag(double *A, double *A_dop, int n, ErrorCode *Error);
void diag(double *A, double *A_dop, int n, ErrorCode *Error)
{
	*Error = OK;
	for (int k = 0; k < (n - 1); k++)
	{
		*Error = MATR_IS_SINGULAR;
		for (int i = k; i < n; i++)
		{
			if (Abs(A[i * n + k]) >= eps)
			{
				*Error = OK;
				swap(A_dop, n, k, i);
				swap(A, n, k, i);

				multiply(A_dop, n, k, 1.0 / A[k * n + k]);
				multiply(A, n, k, 1.0 / A[k * n + k]);
				break;
			}
		}
		if (*Error == OK)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					plus_str(A_dop, n, i, k, -A[i * n + k] / A[k * n + k]);
					plus_str(A, n, i, k, -A[i * n + k] / A[k * n + k]);
				}
		}
		else
			break;
	}
	for (int k = 0; k < n; k++)
		if (Abs(A[k * n + k]) < eps)
			*Error = MATR_IS_SINGULAR;
}

void inverse(double *A, int n, ErrorCode *Error);
void inverse(double *A, int n, ErrorCode *Error)
{
	double *A_dop;
	A_dop = (double*)malloc(n * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j)
				A_dop[i * n + j] = 1;
			else
				A_dop[i * n + j] = 0;

	diag(A, A_dop, n, Error);
	if (*Error != MATR_IS_SINGULAR)
	{
		centr_sym(A, n);
		centr_sym(A_dop, n);
		diag(A, A_dop, n, Error);
		centr_sym(A_dop, n);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = A_dop[i * n + j];
	free(A_dop);
}