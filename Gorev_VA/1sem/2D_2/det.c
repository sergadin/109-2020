#include <stdlib.h>
#include "det.h"

double Abs(double x)
{
	if (x >= 0)
		return x;
	return -x;
}

void centr_sym(double **matr, int n)
{
	double **T;
	T = (double**)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		T[i] = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T[i][j] = matr[n - 1 - i][n - 1 - j];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matr[i][j] = T[i][j];
	for (int i = 0; i < n; i++)
		free(T[i]);
	free(T);
}

void swap(double **matr, int n, int i1, int i2)
{
	double *A = matr[i1];
	matr[i1] = matr[i2];
	matr[i2] = A;
}

void multiply(double **matr, int n, int i1, double c)
{
	for (int j = 0; j < n; j++)
		matr[i1][j] = c * matr[i1][j];
}

void plus_str(double **matr, int n, int i1, int i2, double c)
{
	for (int j = 0; j < n; j++)
		matr[i1][j] = matr[i1][j] + c * matr[i2][j];
}

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
				swap(A, n, k, i);
				if (k != i)
					det = -det;
				break;
			}
		}
		if (q == 0)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					plus_str(A, n, i, k, -A[i][k] / A[k][k]);
				}
		}
		else
			return 0.0;
	}
	for (int k = 0; k < n; k++)
		det *= A[k][k];
	return det;
}
