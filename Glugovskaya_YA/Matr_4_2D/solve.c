#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"
#include "MaxEl.h"
#include "prn_matr.h"


double *Solve_of_system(double **a, int n, int m, double *Solution){
	
	int i, j, l, sgn = 1;;
	double del, kof;
	
	for (i = 0; i < n; i++)
	{		
		if (i < n - 1) sgn *= MaxEl_In_Collon(a, n, m, i);
		
		if (fabs(a[i][i]) > 1e-15)
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
	}
	prn_matr(a, n, m);
	
	
	for (i = 0; i < n; i++) Solution[i] = 1;
	
	if (n < m - 1) {
		 printf("Бесконечно много решений, одно из них:\n");
	}
	
	for (i = n - 1; i >= 0; i--)
	{
		a[i][m-1] /= a[i][i];
		a[i][i] =1;
		Solution[i] = a[i][m-1];

		for (j = i - 1; j >= 0; j--)
		{
			a[j][m-1] -= a[j][i] * a[i][m-1];
			a[j][i] = 0;
		}
	}

	return Solution;
}
