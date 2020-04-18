#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"clin.h"

double* clin(double **matrix2d, int n_rows, int n_cols)
{
	int k, n, j, i;
	double *x;
	n = n_rows;
	for ( k = 0; k < n; k++ )
	{
		if ( fabs( matrix2d[k] [k] ) < 0.0001 )
			{
				printf( "Система не имеет единственного решения" );
				return ( 0 );
			}
		for ( j = n; j >= k; j-- )
			matrix2d[k] [j] /= matrix2d[k] [k];
		for ( i = k + 1; i < n; i++ )
			for ( j = n; j >= k; j-- )
				matrix2d[i] [j] -= matrix2d[k] [j] * matrix2d[i] [k];
	}
	for ( i = 0; i < n; i++ )
		x[i] = matrix2d[i] [n];
	for ( i = n - 2; i >= 0; i-- )
		for ( j = i + 1; j < n; j++ )
			x[i] -= x[j] * matrix2d[i] [j];
	return x;
}


