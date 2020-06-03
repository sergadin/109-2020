#include <stdio.h>
#include <stdlib.h>
#include "zachet.h"

#define E 0.001
#define NUMT 3

int main(void) 
{
	int n, m;
	double *matrix;
	FILE *input, *output;

	if ((input = fopen("input.txt", "r")) == NULL) 
	{
		printf("ERROR open input\n");
		return -1;
	}
       
	if ((output = fopen("output.txt", "w")) == NULL)
	{
		printf("ERROR open output\n");
		fclose(input);
		return -1;
	}
        for (int numt = 0; numt < NUMT; numt++) 
	{
		if ((fscanf(input, "%d%d", &n, &m) != 2))
		{
                        printf("ERROR read matrix\n");
                        fclose(input);
			fclose(output);
                        return -1;
                } 

		if (n <= 0 || m <= 0)
		{
			printf("ERROR n || m");
			fclose(input);
			fclose(output);
		}

                if ((matrix = (double *) malloc(n*m*sizeof(double))) == NULL) 
		{
                        printf("ERROR memory\n");
                        fclose(input);
			fclose(output);
                        return -1;
                }

		for (int i = 0; i < n*m; i++) 
		{
                	if (fscanf(input, "%lf", &matrix[i]) != 1) 
			{
                        	printf("ERROR read matrix\n");
                        	fclose(input);
	                        free(matrix);
        	                return -1;
                	}
        	}

		fprintf(output, "TEST %d\n", (numt+1));
		zachet_matrix(matrix, n, m, E);
		printMatrix(matrix, n, m, output);
	}
	fclose(input);
	fclose(output);
	return 0;

}
