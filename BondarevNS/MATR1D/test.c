#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"rank.h"
#include<stdlib.h>


int main(void)
{
	FILE *input;
	int nrow = 7, ncol = 8;
	int res;
	int tr = 7;
	double el;
	double ** matrix = malloc(nrow * sizeof(double *));
	if((input = fopen("input.txt", "r")) == NULL)
		return -1;
	for(int row = 0; row < nrow; row ++)
	{
		matrix[row] = malloc(ncol * sizeof(double));
	}


	for(int i = 0; i < nrow; i ++)
	{
		for(int j = 0; j < ncol; j ++)
		{
			if(fscanf(input, "%lf", &el) != 1)
				return -1;
			matrix[i][j] = el;
		}
	}
	res = rank(matrix, nrow, ncol);

	
	printf("my:\n%d\ncorrect:\n%d\n", res, tr);

	for(int row = 0; row < nrow; row ++)
	{
		free(matrix[row]);
	}
	free(matrix);
	fclose(input);
}
