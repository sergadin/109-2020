#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"

void PrintMatrix(double *matr, int n);


int main(void)
{	
	int i, n, m;
	double result;
	double *matrix;
	FILE *input;
	FILE *output;
	
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		free(matrix);
		fclose(input);
		return -1;
	}
	
	if((output = fopen("output.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		free(matrix);
		fclose(input);
		fclose(output);
		return -1;
	}
	
	
	if(fscanf(input, "%d %d", &n, %m) != 2)
	{
		fprintf(stdout, "Incorrect size input \n");
		free(matrix);
		fclose(input);
		return -1;
	}
	
	matrix = (double*)malloc(n*m*sizeof(double));
	for(i = 0; i<n*m; ++i)
	{
		if(fscanf(input, "%lf", &matrix[i]) != 1)
		{
			fprintf(stdout, "Incorrect matrix input \n");
			free(matrix);
			fclose(input);
			fclose(output);
			return -1;
		}
	}
	fprintf(stdout, "Initial matrix:");
	PrintMatrix(matrix, n);
	
	fprintf(stdout, "Changed matrix");
	PrintMatrix(matrix, n);
	fprintf(stdout, "det(A) = %lf \n", result);
	free(martrix);
	fclose(input);
	return 0;
}


void PrintMatrix(double *matr, int n)
{
	fprintf(stdout, "\n");	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			fprintf(stdout,"%g ", matr[i*n+j]);
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
} 


