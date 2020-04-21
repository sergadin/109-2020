#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"
#include "MaxEl.h"
#include "prn_matr.h"

double Solve_of_system(double **a, int n, int m){
	
	int i, j, l, sgn = 1;;
	double del, kof, det = 1;
	
	for (i = 0; i < n; i++)
	{		
		if (i < n - 1) sgn *= MaxEl_In_Collon(a, n, m, i);
		
		if (a[i][i] < 0 || a[i][i] > 0)
		{
			
			del = a[i][i];
		
			for (j = i + 1; j < n; j++)
			{
				kof = a[j][i] / del;
			
				for (l = 0; l < m ; l++)
				{
					a[j][l] -= kof * a[i][l];		
				}
			}
		}
		det *= a[i][i];
	}
	
	double *x;
	x = (double*) malloc ((m - 1) * sizeof(double));
	
	for (i = 0; i < n; i++) x[i] = 1;
	
	if (n < m - 1) {
		 printf("Бесконечно много решений, одно из них:\n");
	}
	
	for (i = n - 1; i >= 0; i--)
	{
		a[i][m-1] /= a[i][i];
		a[i][i] =1;
		x[i] = a[i][m-1];

		for (j = i - 1; j >= 0; j--)
		{
			a[j][m-1] -= a[j][i] * a[i][m-1];
			a[j][i] = 0;
		}
	}
	
	printf("Vect\n");
	for (i = 0; i< m-1; i++) printf("%lf ", x[i]);
	
	free(x);
	
	return det * sgn;
}
