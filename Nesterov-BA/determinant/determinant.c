#include <stdlib.h>
#include <math.h>
#include "determinant.h"

double ABS(double x)
{
	if (x<0)
		return -x;
	else
		return x;
}

void SwapRows(double *matrix, int n, int row1, int row2)
{
	double a;
	int i;
	for(i = 0; i<n; ++i)
		{
			a = matrix[row1*n + i];
			matrix[row1*n + i] = matrix[row2*n + i];
			matrix[row2*n + i] = a;
		}
}

void PlusRow(double *matrix, int n, int row1, int row2, double c)
{
	int i;
	for (int i = 0; i < n; i++)
		matrix[row1*n+i] = matrix[row1*n+i] + c * matrix[row2*n+i];
}

double Det(double *matrix, int n)
{
	int q;
	double det = 1;
	for (int k = 0; k < (n - 1); k++)
	{
		q = 1;
		for (int i = k; i < n; i++)
		{
			if (ABS(matrix[i*n+k]) >= eps)
			{
				q = 0;
				SwapRows(matrix, n, k, i);
				if (k != i)
				{
					det = -det;
				}
				break;
			}
		}
		if (q == 0)
		{
			for (int i = k + 1; i < n; i++)
				for (int j = k; j < n; j++)
				{
					PlusRow(matrix, n, i, k, -matrix[i*n+k] / matrix[k*n+k]);
				}
		}
		else
			return 0.0;
	}
	for (int k = 0; k < n; k++)
		det = det*matrix[k*n+k];
	return det;
}
