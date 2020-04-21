#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main(void)
{
	int N;
	int i, j, k;
	FILE *input;
	double **matrix;
	double **matrixinv;
	int inv_existence, true_inv_existence, correctness;
	double t;

	input = fopen("input.txt", "r");
	for(i = 0; i < 4; i++)
	{
		fprintf(stdout, "Test #%d\n", i+1);

		fscanf(input, "%d", &N);

		matrix = malloc(N * sizeof(double *));
		matrixinv = malloc(N * sizeof(double *));
		for(j = 0; j < N; j++)
		{
			matrix[j] = malloc(N * sizeof(double));
			matrixinv[j] = malloc(N * sizeof(double));
		}

		for(j = 0; j < N; j++)
			for(k = 0; k < N; k++)
				fscanf(input, "%lf", &matrix[j][k]);

		fscanf(input, "%d", &true_inv_existence);
		inv_existence = inv(matrix, matrixinv, N);
		
		if(inv_existence != true_inv_existence)
			fprintf(stdout, "Incorrect answer :(\n");
		else if(inv_existence == 0)
			fprintf(stdout, "Correct answer :)\n");
		else
		{
			correctness = 1;
			for(j = 0; j < N; j++)
			{
				for(k = 0; k < N; k++)
				{
					fscanf(input, "%lf", &t);
					if(!(fabs(t - matrixinv[j][k]) < eps))
						correctness = 0;
				}
			}
			if(correctness == 0)
				fprintf(stdout, "Incorrect answer :(\n");
			else
				fprintf(stdout, "Correct answer :)\n");		
		}

		for(j = 0; j < N; j++)
		{
			free(matrix[j]);
			free(matrixinv[j]);
		}
		free(matrix);
		free(matrixinv);

	}
	fclose(input);

	return 0;
}
