#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zachet.h"

#define matrix(m, i, j) matrix[(i) * (m) + (j)]

void printMatrix(double *matrix, int n, int m, FILE *output);
double zachet_matrix(double *matrix, int n, int m, double E) 
{
	int max_index = 0, str_index = 0;
	double max;
	for(int i = 0; i < n; i++)
	{
		max = matrix(m, i, 0);
		for (int j = 0; j < m; j++)
		{
			if (matrix(m, i, j) - max > E)
			{
				max = matrix(m, i, j);
				if (j > max_index)
				{
					max_index = j;
					str_index = i;
				}
			}
		}
	}

	printf("%d %d\n", max_index, str_index);
	for (int p = 0; p < n; p++)
	{

		for (int i = 0; i < m; i++)
		{

			matrix(m, p, i) = (matrix(m, p, i) + matrix(m, str_index, i))/2;

		}

	}	

}


void printMatrix(double *matrix, int n, int m, FILE *output)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(output, "%lf ", matrix(m, i, j));
		}
		fprintf(output, "\n");
	}
	free(matrix);
}
