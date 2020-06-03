#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zachet.h"

#define matrix(n, i, j) matrix[(i) * (n) + (j)]

void printMatrix(double *matrix, int n, int m, FILE *output);
double zachet_matrix(double *matrix, int n, int m, double E) 
{
	int max_index = 0, str_index = 0;
	double max;
	for(int i = 0; i < n; i++)
	{
		max = matrix(n, i, 0);
		for (int j = 0; j < m - 1; j++)
		{
			if (matrix(n, i, j + 1) - max > E)
			{
				max = matrix(n, i, j + 1);
				if (j + 1 > max_index)
				{
					max_index = j + 1;
					str_index = i;
				}
			}
		}
	}

	for (int p = 0; p < n; p++)
	{
		if (p != str_index)
		{
			for (int i = 0; i < m; i++)
			{

				matrix(n, p, i) = (matrix(n, p, i) + matrix(n, str_index, i))/2;

			}
		}
	}	

}


void printMatrix(double *matrix, int n, int m, FILE *output)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(output, "%lf ", matrix(n, i, j));
		}
		fprintf(output, "\n");
	}
	free(matrix);
}
