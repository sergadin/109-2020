#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Det.h"

#define EPS 0.000001
#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

int main(void)
{
	FILE *fin, *fout;
	double ca; // calculated_answer
	double ea; // exact_answer
	double **matrix;
  int cot; // count_of_tests
	int n, i, j, k, l;
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Input file doesn't exist\n");
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		printf("Ouput file doesn't exist\n");
		fclose(fin);
		return -1;
	}
  if (fscanf(fin, "%d", &cot) != 1)
  {
    fprintf(fout, "Invalid input file format\n");
    fclose(fin);
    fclose(fout);
    return -1;
  }
  for (l = 0; l < cot; l++)
  {
    fprintf(fout, "Test № %d:", (l + 1));
  	if (fscanf(fin, "%d", &n) != 1)
  	{
  		fprintf(fout, " LOSS | Unexpected error. Invalid input file format\n");
  		fclose(fin);
  		fclose(fout);
  		return -1;
  	}
	if (n <= 1)
	{

  		fprintf(fout, " LOSS | Unexpected error. Invalid input format\n");
		fclose(fin);
		fclose(fout);
		return -1;
	}
  	if ((matrix = (double**) malloc(n * sizeof(double*))) == NULL)
  	{
  		fprintf(fout, " LOSS | Unexpected error. Memory allocation error\n");
  		fclose(fin);
  		fclose(fout);
  		return -1;
  	}
  	for (i = 0; i < n; i++)
  	{
  		if ((matrix[i] = (double *) malloc(n * sizeof(double))) == NULL)
  		{
  			fprintf(fout, " LOSS | Unexpected error. Memory allocation error\n");
  			fclose(fin);
  			fclose(fout);
  			for (j = 0; j < i; j++)
  			{
  				free(matrix[j]);
  			}
  			free(matrix);
  			return -3;
  		}
  	}
  	for(i = 0; i < n; i++)
  	{
  		for (j = 0; j < n; j++)
  		{
  			if (fscanf(fin, "%lf", &matrix[i][j]) != 1)
  			{
  				fprintf(fout, " LOSS | Unexpected error. Invalid input file format\n");
  				fclose(fin);
  				fclose(fout);
  				for (k = 0; k < n; k++)
  				{
  					free(matrix[k]);
  				}
  				free(matrix);
  				return -1;
  			}
  		}
  	}
    if (fscanf(fin, "%lf", &ea) != 1)
    {
      fprintf(fout, " LOSS | Unexpected error. Invalid input file format\n");
      fclose(fin);
      fclose(fout);
      for (i = 0; i < n; i++)
      {
        free(matrix[i]);
      }
      free(matrix);
      return -1;
    }
  	ca = determinant(n, matrix, EPS/n);
    for (i = 0; i < n; i++)
    {
      free(matrix[i]);
    }
    free(matrix);
    if (fabs(ea - ca) < MAXOF3(ea, ca, 1) * EPS)
    {
      fprintf(fout, " OK | Exact answer: %6.10f | Calculated answer: %6.10f | Error value: %1.10f\n", ea, ca, fabs(ea - ca));
    }
    else
    {
      fprintf(fout, " LOSS | Exact answer: %6.10f | Calculated answer: %6.10f | Error value: %1.10f\n", ea, ca, fabs(ea - ca));
      fclose(fin);
      fclose(fout);
			return -1;
    }
  }
  fclose(fin);
  fclose(fout);
	return 0;
}
