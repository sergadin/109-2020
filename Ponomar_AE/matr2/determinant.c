#include <math.h>
#include "determinant.h"

#define matrix(n, i, j) matrix[(i) * (n) + (j)]

double determinant_matrix(double *matrix, int n, double E) 
{
	double factor, change, determinant = 1, sign = 1;
	int string;

	for (int j = 0; j < n; j++) 
	{
		string = j;
		for (int i = j + 1; i < n; i++) 
		{
			if (fabs(matrix(n, i, j)) > fabs(matrix(n, string, j))) 
			{
				string = i;
			}
		}

		if (string != j) 
		{
			for (int a = 0; a < n; a++) 
			{
				change = (matrix(n, j, a));
				matrix(n, j, a) = matrix(n, string, a);
				matrix(n, string, a) = change;
			}

			sign *= -1;
		}

		for (int a = j + 1; a < n; a++) 
		{
			factor = matrix(n, a, j)/matrix(n, j, j);
			for (int b = j; b < n; b++) 
			{
				matrix(n, a, b) -= factor*matrix(n, j, b);
			}
		}

		determinant *= matrix(n, j, j);
	}

	return sign * determinant;
}
