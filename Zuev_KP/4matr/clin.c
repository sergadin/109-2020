#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"clin.h"
static double modul(double x);
static void glavelem(int k, double **mas, int n_rows);

double* clin(double **mas, int n_rows, int n_cols)
{
	int k, j, i;
	double *x = malloc(n_rows* sizeof(double));
	for ( k = 0; k < n_rows; k++ )
	{	
		glavelem(k, mas, n_rows);
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
		{
			x[i] -= x[j] * mas[i] [j];
		}
	return x;
}

static double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

static void glavelem( int k, double **mas, int n_rows)
{
	int i, j, i_max = k, j_max = k;
	double t;
		for ( i = k; i < n_rows; i++ )
			for ( j = k; j < n_rows; j++ )
				if (modul(mas[i_max] [j_max]) < modul(mas[i] [j] ))
				{
					i_max = i;
					j_max = j;
				}
	for ( j = k; j < n_rows + 1; j++ )
	{
		t = mas[k] [j];
		mas[k] [j] = mas[i_max] [j];
		mas[i_max] [j] = t;
	}
	for ( i = 0; i < n_rows; i++ )
	{
		t = mas[i] [k];
		mas[i] [k] = mas[i] [j_max];
		mas[i] [j_max] = t;
	}
}

