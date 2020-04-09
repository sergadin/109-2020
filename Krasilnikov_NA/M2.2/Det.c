#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Det.h"

#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

double determinant(int n, double **matrix, double epsilon)
{
  double det = 1, sign = 1, memory;
  int rwmeoc, i, j, k; //row_with_max_element_of_column
  for (j = 0; j < n; j++)
  {
    rwmeoc = j;
    for (i = (j + 1); i < n; i++)
    {
      if (fabs(matrix[i][j]) > fabs(matrix[rwmeoc][j]))
      {
        rwmeoc = i;
      }
    }
    if (fabs(matrix[j][i]) < MAXOF2(fabs(matrix[j][i]), 1) * epsilon)
    {
      return 0;
    }
    if (rwmeoc != j)
    {
      for (i = 0; i < n; i ++)
      {
        memory = matrix[rwmeoc][i];
        matrix[rwmeoc][i] = matrix[j][i];
        matrix[j][i] = memory;
      }
      sign *= (-1);
    }
    if (matrix[j][j] < 0)
    {
      for (i = 0; i < n; i++)
      {
        matrix[j][i] *= (-1)
      }
      sign *= (-1);
    }
    for (i = (j + 1); i < n; i++)
    {
      if (matrix[j][i] > 0)
      {
        for (k = 0; k < n; k++)
        {
          matrix[j][k] *= (-1)
        }
        sign *= (-1);
      }
      if (fabs(matrix[j][i]) > MAXOF2(fabs(matrix[j][i]), 1) * epsilon)
      {
        for (k = 0; k < n; k++)
        {
          matrix[j][k] = matrix[j][k] / fabs(matrix[j][i]);
          det = det * fabs(matrix[j][i]);
          matrix[j][k] = matrix[j][k] * fabs(matrix[j][rwmeoc]);
          det = det / fabs(matrix[j][rwmeoc]);
          matrix[j][k] = matrix[j][k] + matrix[j][rwmeoc];
        }
      }
    }
  }
  for (i = 0; i < n; i++)
  {
    det *= matrix[i][i];
  }
  det *= sign;
  return det;
}

void print(double **matrix, int n)
{
  int i, j;
  for (i = 0; i < n, i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%lf", matrix[i][j]);
    }
    printf("\n");
  }
}
