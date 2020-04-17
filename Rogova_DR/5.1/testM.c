#include<stdio.h>
#include<math.h>
#include"rank.h"
#include<stdlib.h>


int main(void)
{
	FILE *input1;
        FILE *input2;
        FILE *input3;
	int nrow = 7, ncol = 8;
	int an1, an2, an3;
	double el;
	int tr1 = 7, tr2 = 1, tr3 = 1;
	double ** matrix = malloc(nrow * sizeof(double *));
	if((input1 = fopen("input1.txt", "r")) == NULL)
		return -1;
	if((input2 = fopen("input2.txt", "r")) == NULL)
		return -1;
	if((input3 = fopen("input3.txt", "r")) == NULL)
		return -1;
	for(int row = 0; row < nrow; row ++)
	{
		matrix[row] = malloc(nrow * sizeof(double));
	}


	for(int i = 0; i < nrow; i ++)
	{
		for(int j = 0; j < ncol; j ++)
		{
			if(fscanf(input1, "%lf", &el) != 1)
				return -1;
			matrix[i][j] = el;
		}
	}
	an1 = frank(matrix, nrow, ncol);

	for(int i = 0; i < nrow; i ++)
	{
		for(int j = 0; j < ncol; j ++)
		{
			if(fscanf(input2, "%lf", &el) != 1)
				return -1;
			matrix[i][j] = el;
		}
	}
	an2 = frank(matrix, nrow, ncol);

	for(int i = 0; i < nrow; i ++)
	{
		for(int j = 0; j < ncol; j ++)
		{
			if(fscanf(input3, "%lf", &el) != 1)
				return -1;
			matrix[i][j] = el;
		}
	}
	an3 = frank(matrix, nrow, ncol);
	printf("my:\n%d\ncorrect:\n%d\n", an1, tr1);
	
	printf("my:\n%d\ncorrect:\n%d\n", an2, tr2);
	
	printf("my:\n%d\ncorrect:\n%d\n", an3, tr3);

	for(int row = 0; row < nrow; row ++)
	{
		free(matrix[row]);
	}
	free(matrix);
}
