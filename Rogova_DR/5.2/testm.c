#include<stdio.h>
#include<math.h>
#include"obr.h"
#include<stdlib.h>
#define EL(ncol, row, col)\
	((ncol) * (row) + (col))
double sum_el_mproz(double * m1, double * m2, int n);



int main(void)
{
	FILE *input1;
        FILE *input2;
        FILE *input3;
	int n = 8;
	double el;
	double eps1, eps2, eps3;

	double * matrix = malloc(n * n  * sizeof(double *));
	double * edmatrix = malloc(n * n  * sizeof(double *));
	double * postedmatrix = malloc(n * n  * sizeof(double *));
	double * postmatrix = malloc(n * n  * sizeof(double *));

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
		}
	}

	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(i == j)
				postedmatrix[EL(n, i, j)] = 1;
			else
				postedmatrix[EL(n, i, j)] = 0;
		}
	}
	edmatrix = postedmatrix;
	postmatrix = matrix;
	edmatrix = obr(matrix, n, edmatrix);
	eps1 = sum_el_mproz(postmatrix, edmatrix, n);
	
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(fscanf(input2, "%lf", &el) != 1)
				return -1;
			matrix[EL(n, i, j)] = el;
		}
	}


	edmatrix = postedmatrix;
	postmatrix = matrix;
	edmatrix = obr(matrix, n, edmatrix);
	eps2 = sum_el_mproz(postmatrix, edmatrix, n);

	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(fscanf(input3, "%lf", &el) != 1)
				return -1;
			matrix[EL(n, i, j)] = el;
		}
	}

	edmatrix = postedmatrix;
	postmatrix = matrix;
	edmatrix = obr(matrix, n, edmatrix);
	eps3 = sum_el_mproz(postmatrix, edmatrix, n);

	printf("sum_of_elements_matr_proz_1:\n%lf\n", eps1);
	printf("sum_of_elements_matr_proz_2:\n%lf\n", eps2);
	printf("sum_of_elemets_matr_proz_3:\n%lf\n", eps3);
	free(matrix);
}

double sum_el_mproz(double * m1, double * m2, int n)
{
	double sum = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				sum += m1[EL(n, i, k)]*m2[EL(n, k, j)];
			}

		}
	}
return sum;
}
