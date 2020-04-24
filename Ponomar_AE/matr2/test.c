#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"

#define fin "input.txt"
#define E 0.001
#define M 5

int main(void) 
{
	int n;
	double *matrix, det, true_answer;
	FILE *input;

	if ((input = fopen(fin, "r")) == NULL) 
	{
		fprintf(stderr, "ERROR open %s\n", fin);
		return -1;
	}
       
        for (int numt = 0; numt < M; numt++) 
	{
		if ((fscanf(input, "%d", &n) != 1) || (n <= 0)) 
		{
                        fprintf(stderr, "ERROR read matrix\n");
                        fclose(input);
                        return -1;
                } 

                if ((matrix = (double *) malloc(n*n*sizeof(double))) == NULL) 
		{
                        fprintf(stderr, "ERROR memory\n");
                        fclose(input);
                        return -1;
                }

		for (int i = 0; i < n*n; i++) 
		{
                	if (fscanf(input, "%lf", &matrix[i]) != 1) 
			{
                        	fprintf(stderr, "ERROR read matrix\n");
                        	fclose(input);
	                        free(matrix);
        	                return -1;
                	}
        	}

        	det = determinant_matrix(matrix, n, E);

		if (fscanf(input, "%lf\n", &true_answer) != 1) 
		{
			fprintf(stderr, "ERROR read true_answer\n");
			free(matrix);
			fclose(input);
			return -1;
		}

		fprintf(stdout, "TEST %d real: %lf true: %lf\n", (numt+1), 
				det, true_answer);
		free(matrix);
	}

	fclose(input);
	return 0;
}
