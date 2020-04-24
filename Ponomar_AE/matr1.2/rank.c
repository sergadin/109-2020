#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "rank.h"

#define min(a,b) ((a)<(b) ? (a) : (b))

void swap(double *a, double *b);
void printMatrix(double **matrix, int n, int m);

int rank_matrix(double **matrix, int n, int m, double E) 
{	
	int rank = 0;

	for (int j = 0; j < n; j++) 
	{
		for (int a = j + 1; a < n; a++) 
		{
			if (fabs(matrix[j][j])>E)
			{
				double factor = matrix[a][j]/matrix[j][j];

			        for (int b = j; b < m; b++) 
			        {
					matrix[a][b] -= factor*matrix[j][b];
			        }
			}
		}

	}
	for (int j = 0; j < min(n, m); j++)
	{
		if (fabs(matrix[j][j])>E)
		{
			rank++;
		}
	}
	
	return rank;
}

void printMatrix(double **matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
}
void swap(double *a, double *b) 
{
	double swap = *a;
	*a = *b;
	*b = swap;
}
