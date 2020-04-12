#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sole.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define matrix(n, i, j) matrix[(n) * (i) + (j)]

double find_determinant(int n, double *matrix, double epsilon)
{
	double det = 1, sign = 1, memory, coef;
	int rwmeoc, i, j, k; //row_with_max_element_of_column
	for (j = 0; j < n; j++)
	{
		rwmeoc = j;
		for (i = (j + 1); i < n; i++)
		{
			if (fabs(matrix(n, i, j)) > fabs(matrix(n, rwmeoc, j)))
			{
				rwmeoc = i;
			}
		}
		if (fabs(matrix(n, rwmeoc, j)) < MAXOF2(fabs(matrix(n, rwmeoc, j)), 1) * epsilon)
		{
			return 0;
		}
		if (rwmeoc != j)
		{
			for (i = 0; i < n; i ++)
			{
				memory = matrix(n, rwmeoc, j);
				matrix(n, rwmeoc, j) = matrix(n, j, i);
				matrix(n, j, i) = memory;
			}
			sign *= (-1);
		}
		if (matrix(n, j, j) < 0)
		{
			for (i = 0; i < n; i++)
			{
				matrix(n, j, i) *= (-1);
			}
			sign *= (-1);
		}
		for (i = (j + 1); i < n; i++)
		{
			if (matrix(n, j, i) > 0)
			{
				for (k = 0; k < n; k++)
				{
					matrix(n, i, k) *= (-1);
				}
				sign *= (-1);
			}
			if (fabs(matrix(n, i, j)) > MAXOF2(fabs(matrix(n, i, j)), 1) * epsilon)
			{
				coef = fabs(matrix(n, i, j) / matrix(n, j, j));
				for (k = j; k < n; k++)
				{
					matrix(n, i, k) = matrix(n, i, k) + matrix(n, j, k) * coef;
				}
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		det *= matrix(n, i, i;
	}
	det *= sign;
	return det;
}
