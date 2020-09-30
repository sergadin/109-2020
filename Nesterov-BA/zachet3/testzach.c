#include <stdio.h>
#include <stdlib.h>
#include "zachet3.h"

void PrintMatrix(double *matr, int n, int m);


int main(void)
{	
	int i, j, n, m;
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
	
	if((output = fopen("output.txt","w")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		free(matrix);
		fclose(input);
		fclose(output);
		return -1;
	}
	
	
	if(fscanf(input, "%d %d", &n, &m) != 2)
	{
		fprintf(stdout, "Incorrect size input \n");
		free(matrix);
		fclose(input);
		fclose(output);
		return -1;
	}
	
	if((matrix = (double *)malloc(m * n * sizeof(double))) == NULL)
	{
		fprintf(stderr, "Memory error\n");
		fclose(input);
		return -1;
	}
	for(i = 0; i < m; i++)
	{
		for(j = 0; j<n; j++)
		if(fscanf(input, "%lf", &matrix[j*m+i]) != 1)
		{
			fprintf(stdout, "Wrong input\n");
			fclose(input);
			free(matrix);
			return -1;
		}
	}
	
	fprintf(stdout, "Initial matrix:");
	PrintMatrix(matrix, n, m);
	transform(matrix, n, m);
	fprintf(stdout, "Changed matrix");
	PrintMatrix(matrix, n, m);
	fprintf(output, "%d %d \n", n, m);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fprintf(output,"%g ", matrix[j*m+i]);
			
		}
		fprintf(output, "\n");
	}
	free(matrix);
	fclose(input);
	fclose(output);
	return 0;
}


void PrintMatrix(double *matr, int n, int m)
{
	fprintf(stdout, "\n");	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(stdout,"%g ", matr[i*m+j]);
			
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
} 


