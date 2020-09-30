#include"rank.h"
static void mainelem(int k, double **mas, int n_rows);
double modul(double x);

double rank(double **mas, int n_rows, int n_cols)       
                                                         
{
	int k, j, i; 
	double x;
	x = 0;
	for ( k = 0; k < n_rows; k++ )                   
	{	         
		mainelem(k, mas, n_rows);                             
		for ( j = n_rows; j >= k; j-- )
			mas[k] [j] /= mas[k] [k];
		for ( i = k + 1; i < n_rows; i++ )
			for ( j = n_rows; j >= k; j-- )
				mas[i] [j] -= mas[k] [j] * mas[i] [k];
	}
	
	for(k = n_rows - 1; k >= 0; k--)
		for(i = 0; i < n_cols; i++)
			if ( modul( mas[i] [k] ) > 0.0001)
				{
					x++;
  					break;
				}
				return x;
}


static void mainelem( int k, double **mas, int n_rows)
{
	int i, j, i_max = k, j_max = k;
	double tmp;
		for ( i = k; i < n_rows; i++ )
			for ( j = k; j < n_rows; j++ )
				if (modul(mas[i_max] [j_max]) < modul(mas[i] [j] ))
				{
					i_max = i;
					j_max = j;
				}
	for ( j = k; j < n_rows + 1; j++ )
	{
		tmp = mas[k] [j];
		mas[k] [j] = mas[i_max] [j];
		mas[i_max] [j] = tmp;
	}
	for ( i = 0; i < n_rows; i++ )
	{
		tmp = mas[i] [k];
		mas[i] [k] = mas[i] [j_max];
		mas[i] [j_max] = tmp;
	}
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

