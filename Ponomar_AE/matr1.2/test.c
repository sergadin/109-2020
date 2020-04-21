#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rank.h"

#define min(a,b) ((a)<(b) ? (a) : (b))
#define NUMT 3
#define E 0.0001
#define fin "input.txt"

int main(void) 
{
	FILE *input;
	int n, m, true_answer, rank;
	double **matrix;

	if ((input = fopen(fin, "r")) == NULL) 
	{
		fprintf(stderr, "ERROR open %s\n", fin);
		return -1;
	}

	for (int numt = 0; numt < NUMT; numt++) 
	{
		if ((fscanf(input, "%d%d%d", &n, &m, &true_answer) != 3) || (n<=0) || (m<=0)) 
		{
			fprintf(stderr, "ERROR read N||M||true_answer\n");
			fclose(input);
			return -1;
		}
		
		if ((matrix = (double **) malloc(n*sizeof(double *))) == NULL) 
		{
			fprintf(stderr, "ERROR memory\n");
			fclose(input);
			return -1;
		}

		for (int i = 0; i < n; i++) 
		{
			if ((matrix[i] = (double *) malloc(m * sizeof(double))) == NULL) 
			{
				fprintf(stderr, "ERROR memory %d\n", i + 1);
				for (int j = 0; j < i; j++)
				{
					free(matrix[j]);
				}
				free(matrix);
				fclose(input);
				return -1;
			}
		}

		for (int a1 = 0; a1 < n; a1++) 
		{
			for (int a2 = 0; a2 < m; a2++) 
			{
				if (fscanf(input, "%lf", &(matrix[a1][a2])) != 1) 
				{
					fprintf(stderr, "ERROR read matrix\n");
					for (int i = 0; i < n; i++)
					{
						free(matrix[i]);
					}
					free(matrix);
					fclose(input);
					return -1;
				}
			}
		}
		
		rank = rank_matrix(matrix, n, m, E);
		fprintf(stdout, "TEST %d real: %d true: %d\n", (numt+1), rank, true_answer);
		for (int i = 0; i < n; i++) 
		{
			free(matrix[i]);
		}	
		free(matrix);
	}

	fclose(input);
	return 0;
}
