#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rank.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);
//2 -1 3 -2 4 4 -2 5 1 7 2 -1 1 8 2
int main(void)
{
	int i, j, n_rows = 3, n_cols = 5;
	double current, e = 0.1;
	double **mas = malloc(n_rows* sizeof(double));
	double result;
	double b[] = {2};
	FILE *input1;
	if((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	for(int row = 0; row < n_rows; row++)
	{
		mas[row] = malloc(n_cols* sizeof(double));
	}
	for(i = 0; i < n_rows ; i ++)
	{
		for(j = 0; j < n_cols; j ++)
		{
			fscanf(input1, "%lf", &current);
			mas[i][j] = current;
		}
	}
	result = rank(mas, n_rows, n_cols);
		printf( "%lf\n", result);
	for(i = 0; i < 1; i++)
	{
		if (modul(result - b[i]) < e*MAX1(result, b[i], 1))
		{
			printf("пройден\n");
		}
		else
		{
			printf("не пройден\n");
		}
	}
	for(int row = 0; row < n_rows; row ++)
	{
		free(mas[row]);
	}
	free(mas);
	return 0;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

