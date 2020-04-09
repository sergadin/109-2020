#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Det.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))


double determinant(int n, double **matrix, double epsilon)
{
	double det = 1, sign = 1, memory, coef;
	int rwmeoc, i, j, k; //row_with_max_element_of_column
	print(matrix, n);
	for (j = 0; j < n; j++)
	{
		rwmeoc = j;
		for (i = (j + 1); i < n; i++)
		{
			if (fabs(matrix[i][j]) > fabs(matrix[rwmeoc][j]))
			{;
				rwmeoc = i;
			}
		}
		if (fabs(matrix[rwmeoc][j]) < MAXOF2(fabs(matrix[rwmeoc][j]), 1) * epsilon)
		{
			return 0;
		}
		if (rwmeoc != j)
		{
			for (i = 0; i < n; i ++)
			{
				memory = matrix[rwmeoc][i];
				matrix[rwmeoc][i] = matrix[j][i];
				matrix[j][i] = memory;
			}
			sign *= (-1);
		}
		print(matrix, n);
		if (matrix[j][j] < 0)
		{
			for (i = 0; i < n; i++)
			{
				matrix[j][i] *= (-1);
			}
			sign *= (-1);
		}
		print(matrix, n);
		for (i = (j + 1); i < n; i++)
		{
			if (matrix[i][j] > 0)
			{
				for (k = 0; k < n; k++)
				{
					matrix[i][k] *= (-1);
				}
				sign *= (-1);
			}
			print(matrix, n);
			if (fabs(matrix[i][j]) > MAXOF2(fabs(matrix[i][j]), 1) * epsilon)
			{
				coef = fabs(matrix[i][j]);
				for (k = j; k < n; k++)
				{
					matrix[i][k] = matrix[i][k] / coef;
				}
				print(matrix, n);
				det = det * coef;
				coef = fabs(matrix[j][j]);
				for (k = j; k < n; k++)
				{
					matrix[i][k] = matrix[i][k] * coef;
				}
				det = det / coef;
				print(matrix, n);
				for (k = j; k < n; k++)
				{
					matrix[i][k] = matrix[i][k] + matrix[j][k];
				}
				print(matrix, n);
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		det *= matrix[i][i];
	}
	det *= sign;
	return det;
}

void print(double **matrix, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%g ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
