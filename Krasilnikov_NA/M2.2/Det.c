#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Det.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))

double find_determinant(int n, double **matrix, double epsilon)
{
	double det = 1, sign = 1, memory, coef;
	int rwmeoc; //row_with_max_element_of_column
	for (int j = 0; j < n - 1; j++)
	{
		rwmeoc = j;
		for (int i = (j + 1); i < n; i++)
		{
			if (fabs(matrix[i][j]) > fabs(matrix[rwmeoc][j]))
			{
				rwmeoc = i;
			}
		}
		if (fabs(matrix[rwmeoc][j]) < MAXOF2(fabs(matrix[rwmeoc][j]), 1) * epsilon)
		{
			return 0;
		}
		if (rwmeoc != j)
		{
			for (int i = 0; i < n; i ++)
			{
				memory = matrix[rwmeoc][i];
				matrix[rwmeoc][i] = matrix[j][i];
				matrix[j][i] = memory;
			}
			sign *= (-1);
		}
		if (matrix[j][j] < 0)
		{
			for (int i = 0; i < n; i++)
			{
				matrix[j][i] *= (-1);
			}
			sign *= (-1);
		}
		for (int i = (j + 1); i < n; i++)
		{
			if (matrix[i][j] > 0)
			{
				for (int k = 0; k < n; k++)
				{
					matrix[i][k] *= (-1);
				}
				sign *= (-1);
			}
			coef = fabs(matrix[i][j] / matrix[j][j]);
			for (int k = j; k < n; k++)
			{
				matrix[i][k] = matrix[i][k] + matrix[j][k] * coef;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		det *= matrix[i][i];
	}
	det *= sign;
	return det;
}
