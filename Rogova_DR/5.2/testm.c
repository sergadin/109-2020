#include<stdio.h>
#include<math.h>
#include"obr.h"
#include<stdlib.h>
#define EL(ncol, row, col)\
	((ncol) * (row) + (col))

int main(void)
{
	FILE *input1;
        FILE *input2;
        FILE *input3;
	int n = 2;
	double el;

	double * NUL = malloc(n * n * sizeof(double));
	double * matrix = malloc(n * n  * sizeof(double ));
	double * edmatrix = malloc(n * n  * sizeof(double ));
	double * postedmatrix = malloc(n * n  * sizeof(double ));

	if((input1 = fopen("input1.txt", "r")) == NULL)
		return -1;
	if((input2 = fopen("input2.txt", "r")) == NULL)
		return -1;
	if((input3 = fopen("input3.txt", "r")) == NULL)
		return -1;

	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(fscanf(input1, "%lf", &el) != 1)
				return -1;
			matrix[EL(n, i, j)] = el;
			printf("\n%lf\n", matrix[EL(n, i, j)]);
		}
	}
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
			NUL[EL(n, i, j)] = 0;
	}

	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(i == j)
				edmatrix[EL(n, i, j)] = 1;
			else
				edmatrix[EL(n, i, j)] = 0;
		}
        }
	postedmatrix = edmatrix;
        edmatrix = obr(matrix, n, edmatrix, NUL);
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			
			printf("elem_m1(%d,%d):\n%lf\n",i, j, edmatrix[EL(n, i, j)]);
		}
	}
 	
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(fscanf(input2, "%lf", &el) != 1)
				return -1;
			matrix[EL(n, i, j)] = el;
			printf("\n%lf\n", matrix[EL(n, i, j)]);
		}
	}
	edmatrix = postedmatrix;
	edmatrix = obr(matrix, n, edmatrix, NUL);
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			
			printf("elem_m2(%d,%d):\n%lf\n",i, j, edmatrix[EL(n, i, j)]);
		}
	}

	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(fscanf(input3, "%lf", &el) != 1)
				return -1;
			matrix[EL(n, i, j)] = el;
			printf("\n%lf\n", matrix[EL(n, i, j)]);
		}
	}
	edmatrix = postedmatrix;
	edmatrix = obr(matrix, n, edmatrix, NUL);
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			
			printf("elem_m3(%d,%d):\n%lf\n",i, j, edmatrix[EL(n, i, j)]);
		}
	}

	free(matrix);
	free(NUL);

}

