#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sole.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define matrix(n, i, j) matrix[(n) * (i) + (j)]

int definition_test(int n, double *matrix, double epsilon)
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
		else
		{
			return 1;
		}
	}
}

double *find_solution(int n, double *matrix, double epsilon)
{
	double memory, coef;
	print(matrix, n);
	int rwmeoc, i, j, k; //row_with_max_element_of_column
	for (j = 0; j < (n - 1); j++)
	{
		rwmeoc = j;
		for (i = (j + 1); i < n; i++)
		{
			if (fabs(matrix((n + 1), i, j)) > fabs(matrix((n + 1), rwmeoc, j)))
			{
				rwmeoc = i;
			}
		}
		if (rwmeoc != j)
		{
			for (i = 0; i < (n + 1); i ++)
			{
				memory = matrix((n + 1), rwmeoc, i);
				matrix((n + 1), rwmeoc, i) = matrix((n + 1), j, i);
				matrix((n + 1), j, i) = memory;
			}
		}
		print(matrix, n);
		if (matrix((n + 1), j, j) < 0)
		{
			for (i = 0; i < n + 1; i++)
			{
				matrix((n + 1), j, i) *= (-1);
			}
		}
		print(matrix, n);
		for (i = (j + 1); i < n; i++)
		{
			if (matrix((n + 1), i, j) > 0)
			{
				for (k = 0; k < (n + 1); k++)
				{
					matrix((n + 1), i, k) *= (-1);
				}
			}
			print(matrix, n);
			coef = fabs(matrix((n + 1), i, j) / matrix((n + 1), j, j));
			for (k = j; k < (n + 1); k++)
			{
				matrix((n + 1), i, k) = matrix((n + 1), i, k) + matrix((n + 1), j, k) * coef;
			}
		}
	}
	print(matrix, n);
	for (j = (n - 1); j > -1; j--)
	{
		if (matrix((n + 1), j, j) < 0)
		{
			matrix((n + 1), j, j) *= (-1);
			matrix((n + 1), j, n) *= (-1);
		}
		print(matrix, n);	
		for (i = (j - 1); i > -1; i--)
		{
			if (fabs(matrix((n + 1), i, j)) > MAXOF2(fabs(matrix((n + 1), i, j)), 1) * epsilon)
			{
		
				if (matrix((n + 1), i, j) > 0)
				{
					for (k = 0; k < (n + 1); k++)
					{
						matrix((n + 1), i, k) *= (-1);
					}
				}
				coef = fabs(matrix((n + 1), i, j)) / matrix((n + 1), j, j);
				matrix((n + 1), i, j) = matrix((n + 1), i, j) + matrix((n + 1), j, j) * coef;
				matrix((n + 1), i, n) = matrix((n + 1), i, n) + matrix((n + 1), j, n) * coef;
			}
		}
	}
	print(matrix, n);
	for (j = 0; j < n; j++)
	{
		matrix((n + 1), j, n) = matrix((n + 1), j, n) / matrix((n + 1), j, j);
		matrix((n + 1), j, j) = matrix((n + 1), j, j) / matrix((n + 1), j, j);
	}	
	print(matrix, n);
}

void print(double *matrix, int n)
{
	int i;
	printf("\n");
	for (i = 0; i < n * (n + 1); i ++)
	{
		printf("%lf ", matrix[i]);
		if (i % (n + 1) == n)
		{
			printf("\n");
		}
	}
}
