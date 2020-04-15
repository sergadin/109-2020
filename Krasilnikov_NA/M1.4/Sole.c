#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sole.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MATRIX(n, i, j) mos[(n) * (i) + (j)]

double *solve_system(int n, double *mos, double epsilon, ErrorCode *error)
{
	double memory, coef, *solution;
	int rwmeoc; //row_with_max_element_of_column
	*error = SYSTEM_OK;
	if ((solution = (double *) malloc(n * sizeof(double))) == NULL)
	{
		*error = ALLOCATION_ERROR;		
		return NULL;
	}
	for (int j = 0; j < n; j++)
	{
		rwmeoc = j;
		for (int i = (j + 1); i < n; i++)
		{
			if (fabs(MATRIX((n + 1), i, j)) > fabs(MATRIX((n + 1), rwmeoc, j)))
			{
				rwmeoc = i;
			}
		}
		if (fabs(MATRIX((n + 1), rwmeoc, j)) < MAXOF2(fabs(MATRIX((n + 1), rwmeoc, j)), 1) * epsilon)
		{
			*error = NOT_DEFINED;
			return NULL;
		}
		if (rwmeoc != j)
		{
			for (int i = 0; i < (n + 1); i ++)
			{
				memory = MATRIX((n + 1), rwmeoc, i);
				MATRIX((n + 1), rwmeoc, i) = MATRIX((n + 1), j, i);
				MATRIX((n + 1), j, i) = memory;
			}
		}
		if (MATRIX((n + 1), j, j) < 0)
		{
			for (int i = 0; i < n + 1; i++)
			{
				MATRIX((n + 1), j, i) *= (-1);
			}
		}
		for (int i = (j + 1); i < n; i++)
		{
			if (MATRIX((n + 1), i, j) > 0)
			{
				for (int k = 0; k < (n + 1); k++)
				{
					MATRIX((n + 1), i, k) *= (-1);
				}
			}
			coef = fabs(MATRIX((n + 1), i, j) / MATRIX((n + 1), j, j));
			for (int k = j; k < (n + 1); k++)
			{
				MATRIX((n + 1), i, k) = MATRIX((n + 1), i, k) + MATRIX((n + 1), j, k) * coef;
			}
		}
	}
	for (int j = (n - 1); j > -1; j--)
	{
		if (MATRIX((n + 1), j, j) < 0)
		{
			MATRIX((n + 1), j, j) *= (-1);
			MATRIX((n + 1), j, n) *= (-1);
		}
		for (int i = (j - 1); i > -1; i--)
		{
			if (fabs(MATRIX((n + 1), i, j)) > MAXOF2(fabs(MATRIX((n + 1), i, j)), 1) * epsilon)
			{
				if (MATRIX((n + 1), i, j) > 0)
				{
					for (int k = 0; k < (n + 1); k++)
					{
						MATRIX((n + 1), i, k) *= (-1);
					}
				}
				coef = fabs(MATRIX((n + 1), i, j)) / MATRIX((n + 1), j, j);
				MATRIX((n + 1), i, j) = MATRIX((n + 1), i, j) + MATRIX((n + 1), j, j) * coef;
				MATRIX((n + 1), i, n) = MATRIX((n + 1), i, n) + MATRIX((n + 1), j, n) * coef;
			}
		}
	}
	for (int j = 0; j < n; j++)
	{
		MATRIX((n + 1), j, n) = MATRIX((n + 1), j, n) / MATRIX((n + 1), j, j);
		MATRIX((n + 1), j, j) = MATRIX((n + 1), j, j) / MATRIX((n + 1), j, j);
	}
	for (int j = 0; j < n; j++)
	{
		solution[j] = MATRIX((n + 1), j, n);
	}	
	return solution;
}
