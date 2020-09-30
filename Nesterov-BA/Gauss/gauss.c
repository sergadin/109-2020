#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "gauss.h"

double ABS(double x)
{
	if (x<0)
		return -x;
	else
		return x;
}

void SwapRows(double **matrix, int n, int row1, int row2)
{
	double *a;
	int i;
	a = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = a;
}

void PlusRow(double **matrix, int n, int row1, int row2, double c)
{
	int i;
	for (int i = 0; i < n+1; i++)
		matrix[row1][i] = matrix[row1][i] + c * matrix[row2][i];
}

void MultRow(double **matrix, int n, int row, double c)
{
	for(int i=0; i<n+1; ++i)
	{
		matrix[row][i] *= c;
	}
}

void Gauss(double **matrix, int n)
{
	int q;
	for (int k = 0; k < (n - 1); k++)
	{
		q = 1;
		for (int i = k; i < n; i++)
		{
			if (ABS(matrix[i][k]) >= eps)
			{
				q = 0;
				SwapRows(matrix, n, k, i);
				break;
			}
		}
		if (q == 0)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					PlusRow(matrix, n, i, k, -matrix[i][k] / matrix[k][k]);
				}
		}
	}
	
	for(int k = 0; k<n; ++k)
	{
		MultRow(matrix, n, k, 1/matrix[k][k]);
	}
	
	for(int k = n-2; k>-1; --k)
	{
		for(int i = n-1; i>k; --i)
		{
			PlusRow(matrix, n, k, i, -matrix[k][i]);
		}
	}
}
