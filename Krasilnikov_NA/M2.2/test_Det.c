#include <stdio.h>
#include <stdlib.h>
#include "Det.h"
#define EPS 0.000001

int main(void)
{
	FILE *fin, *fout, *fans;
	double ca;
	double ea;
	double **matrix;
	int n, i, j, k;
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Input file doesn't exist\n");
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		printf("Ouput file doesn't exist\n");
		fclose(fin);
		return -1;
	}
	if ((fans = fopen("output.txt", "r")) == NULL)
	{
		fprintf(fout, "Answers file doesn't exist\n");
		fclose(fin);
		fclose(fout);
		return -1;
	}
	if (fscanf(fin, "%d", &n) != 1)
	{
		fprintf(fout, "Invalid input file format\n");
		fclose(fin);
		fclose(fout);
		fclose(fans);
		return -1;
	}
	if ((matrix = (double**) malloc(n * sizeof(double*))) == NULL)
	{
		fprintf(fout, "Memory allocation error\n");
		fclose(fin);
		fclose(fout);
		fclose(fans);
		return -2;
	}
	for (i = 0; i < n; i++)
	{
		if ((matrix[i] = (double *) malloc(n * sizeof(double))) == NULL)
		{
			fprintf(fout, "Memory allocation error\n");
			fclose(fin);
			fclose(fout);
			fclose(fans);
			for (j = 0; j < i; j++)
			{
				free(matrix[j]);
			}
			free(matrix);
			return -3;
		}
	}
	for(i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (fscanf(fin, "%lf", &matrix[i][j]) != 1)
			{
				fprintf(fout, "Invalid input file format\n");
				fclose(fin);
				fclose(fout);
				fclose(fans);
				for (k = 0; k < n; k++)
				{
					free(matrix[k]);
				}
				free(matrix);
				return -1;
			}
		}
	}
	ca = determinant(n, matrix, EPS);
	printf("%lf", ca);
	return 0;
}
