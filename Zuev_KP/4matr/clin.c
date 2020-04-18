#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"clin.h"
static double modul(double x);

double* clin(double **mas, int n_rows, int n_cols)
{
	int k, j, i;
	double *x = malloc(n_rows* sizeof(double));
	for ( k = 0; k < n_rows; k++ )
	{
		if ( modul( mas[k] [k] ) < 0.0001 )
		{
			printf( "infinity");
			return 0;
		}
		for ( j = n_rows; j >= k; j-- )
			mas[k] [j] /= mas[k] [k];
		for ( i = k + 1; i < n_rows; i++ )
			for ( j = n_rows; j >= k; j-- )
				mas[i] [j] -= mas[k] [j] * mas[i] [k];
	}
	for ( i = 0; i < n_rows; i++ )
	{
		x[i] = mas[i] [n_rows];
	}
	for ( i = n_rows - 2; i >= 0; i-- )
		for ( j = i + 1; j < n_rows; j++ )
			x[i] -= x[j] * mas[i] [j];
	free(x);
	return x;
}

static double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
