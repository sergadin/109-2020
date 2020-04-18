#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "clin.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);

int main(void)
{
	int i, j, n_rows = 3, n_cols = 4;
	double current, e = 0.1;
	double **mas = malloc(n_rows* sizeof(double));
	double *x1 = malloc(n_rows* sizeof(double));
	double b[] = {0, -1, 2};
	FILE *input1;
	int o[n_rows];
	for ( i = 0; i < n_rows; i++ )
		o[i] = i;
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
	x1 = clin(mas, n_rows, n_cols);
	for ( i = 0; i < n_rows; i++ )
	{
		for ( j = 0; j < n_rows; j++ )
		{
			if ( i == o[j] )
			{
				printf( "%lf\n", x1[j] );
				break;
			}
		}
	}
	for(i = 0; i < n_rows; i++)
	{
		if (modul(x1[i] - b[i]) < e*MAX1(x1[i], b[i], 1))
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
	free(x1);
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
