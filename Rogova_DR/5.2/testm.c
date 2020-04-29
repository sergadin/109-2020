#include<stdio.h>
#include<math.h>
#include"obr.h"
#include<stdlib.h>
#define EL(ncol, row, col)\
	((ncol) * (row) + (col))
void readm(double * matrix, int n, FILE * input);
void makeited(double * edmatrix, int n);
void printm(double * matrix, int n);
double * proz(double * m1, double * m2, int n, double * nul);
void makeitnul(double * nul, int n);
void copy2to1(double * m1, double * m2, int n);

int main(void)
{
	FILE *input1;
        FILE *input2;
        FILE *input3;
	int n = 2;
	double el;
	double * nul = malloc(n * n * sizeof(double));
	double * postmatrix = malloc(n * n * sizeof(double));
	double * matrix = malloc(n * n  * sizeof(double ));
	double * edmatrix = malloc(n * n  * sizeof(double ));

	if((input1 = fopen("input1.txt", "r")) == NULL)
		return -1;
	if((input2 = fopen("input2.txt", "r")) == NULL)
		return -1;
	if((input3 = fopen("input3.txt", "r")) == NULL)
		return -1;
	readm(matrix, n, input1);
	copy2to1(postmatrix, matrix, n);
	makeited(edmatrix, n);
	makeitnul(nul, n);
	obr(matrix, n, edmatrix);
	nul = proz(postmatrix, edmatrix, n, nul);
	printm(postmatrix, n);
	printm(nul, n);

	readm(matrix, n, input2);
	copy2to1(postmatrix, matrix, n);
	makeited(edmatrix, n);
	makeitnul(nul, n);
	obr(matrix, n, edmatrix);
       	nul = proz(postmatrix, edmatrix, n, nul);
	printm(postmatrix, n);
	printm(nul, n);

	readm(matrix, n, input3);
	copy2to1(postmatrix, matrix, n);
	makeited(edmatrix, n);
	makeitnul(nul, n);
	obr(matrix, n, edmatrix);
	nul = proz(postmatrix, edmatrix, n, nul);
	printm(postmatrix, n);
	printm(nul, n);

	fclose(input1);
	fclose(input2);
	fclose(input3);

	free(nul);
	free(postmatrix);
	free(edmatrix);
	free(matrix);

}
void copy2to1(double * m1, double * m2, int n)
{

	for(int i = 0; i < n; i++)
	{
		for(int j  = 0; j < n; j++)
		{
			m1[EL(n, i, j)] = m2[EL(n, i, j)];
		}
	}
}
void  makeitnul(double * nul, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j  = 0; j < n; j++)
		{
			nul[EL(n, i, j)] = 0;
		}
	}
}
double * proz(double * m1, double * m2, int n, double * nul)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				nul[EL(n, i, j)] += m1[EL(n, i, k)]*m2[EL(n, k, j)];
			}
		}
	}
	return nul;
}
void readm(double * matrix, int n, FILE * input)
{
	double el;
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			if(fscanf(input, "%lf", &el) == 1)
				matrix[EL(n, i, j)] = el;
				
		}
	}
}
void makeited(double * edmatrix, int n)
{

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
}
void printm(double * matrix, int n)
{
	printf("\nMATRIX:\n");
	for(int i = 0; i < n; i ++)
	{
		for(int j = 0; j < n; j ++)
		{
			
			printf("elem_m(%d,%d):\n%lf\n",i, j, matrix[EL(n, i, j)]);
		}
	}
}
