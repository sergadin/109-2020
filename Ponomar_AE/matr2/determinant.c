#include <math.h>
#include "determinant.h"

#define matrix(n, i, j) matrix[(i) * (n) + (j)]

double determinant_matrix(double *matrix, int n, double E) 
{
	double factor, change, determinant = 1, sign = 1;
	int string, i, j = 0, a1 = 0, a2, a3;

	for (j = 0; j < n; j++) 
	{
		string = j;
		for (i = j + 1; i < n; i++) 
		{
			if (fabs(matrix(n, i, j)) > fabs(matrix(n, string, j))) 
			{
				string = i;
			}
		}

		if (string != j) 
		{
			for (a1 = 0; a1 < n; a1++) 
			{
				change = (matrix(n, j, a1));
				matrix(n, j, a1) = matrix(n, string, a1);
				matrix(n, string, a1) = change;
			}

			sign *= -1;
		}

		for (a2 = j + 1; a2 < n; a2++) 
		{
			factor = matrix(n, a2, j)/matrix(n, j, j);
			for (a3 = j; a3 < n; a3++) 
			{
				matrix(n, a2, a3) -= factor*matrix(n, j, a3);
			}
		}

		determinant *= matrix(n, j, j);
	}

	return sign * determinant;
}
