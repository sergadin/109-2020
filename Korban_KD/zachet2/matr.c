#include <stdio.h>
#include <math.h>
#include "matr.h"

#define M_MAX 10
#define N_MAX 10

int read_matrix(double *a, int n, int m, const char *name)
{
    FILE *file;
    int i, len = m*n;

    if( !(file = fopen(name, "r")) )
        return MATR_ERR_OPEN;

    for( i = 0; i < len; i++ )
        if( fscanf(file, "%lf", a + i ) != 1 )
        {
            fclose(file);
            return MATR_ERR_READ;
        }

    fclose(file);
    return MATR_SUCCESS;
}



void print_matrix(double *a, int n, int m)
{
    int i, j,n_max, m_max;
    
    m_max = (m > M_MAX ? M_MAX : m);
    n_max = (n > N_MAX ? N_MAX : n);
    
    for( i = 0; i < n_max; i++ )
    {
        for( j = 0; j < m_max; j++ )
            printf(" %lf ", a[i*m + j]);
        
        printf("\n");
    }
}

