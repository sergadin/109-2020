#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

void PrintMatrix(double **matr, int n);

int main(void)
{	
	int i, j, n;
	FILE *input;
	double **matrix;
	
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		free(matrix);
		fclose(input);
		return -1;
	}
	
	
	if(fscanf(input, "%d", &n) != 1)
	{
		fprintf(stdout, "Incorrect size input \n");
		free(matrix);
		fclose(input);
		return -1;
	}
	
	matrix = (double**)malloc(n * sizeof(double));
	
	for (i = 0; i < n; i++)
		matrix[i] = (double*)malloc((n+1) * sizeof(double));
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n+1; j++)
		{
			if(fscanf(input, "%lf", &matrix[i][j]) != 1)
			{
				fprintf(stdout, "Incorrect matrix input \n");
				free(matrix);
				fclose(input);
				return -1;
			}
		}
	}
	PrintMatrix(matrix, n);
	Gauss(matrix, n);
	PrintMatrix(matrix, n);
	for(i=0; i<n; ++i)
	{
		fprintf(stdout, "x[%d] = %lf \n", i+1, matrix[i][n]);
	}
	free(matrix);
	fclose(input);
	return 0;
}

void PrintMatrix(double **matr, int n)
{
	fprintf(stdout, "\n");	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n+1; j++)
		{
			fprintf(stdout,"%g ", matr[i][j]);
			if(j == n-1)
				fprintf(stdout, "| ");
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
} 
