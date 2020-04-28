#include <math.h>
#include <stdio.h>
#include "matr.h"
#include "rank.h"

int rank_matrix (double **a ,int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        double norm_a = norm_matrix(a, n, m);
        int max_i, max_j;
        if ( find_max_abs_redused(n, a, i , &max_i, &max_j) < 1e-16*norm_a )
        {
            return DETERMINANT_0;
        }
        //printf("imax=%d jmax=%d\n", max_i, max_j);
        if( max_i != i)
        {
            a[i] = a[max_i];
        }
        
        if( max_i != i)
        {
            for(int k = 0; k < n; k++)
            {
                a[k][i] = a[k][max_j];
            }
        }
        for(int j = i+1; j < n ; j++)
        {
            a[i][j] /= a[i][i];;
        }
        
        
        for(int j = i+1 ; j < n; j++)
        {
            for(int k = i+1 ; k < n; k++)
            {
                a[j][k] -= a[i][k]*a[j][i];
            }
        
        }
        /*
        printf("/////////////////////////////////////////////\n%d\n",i);
        print_matrix(a, n, n);
        printf("**\n");
        print_matrix(b, n, n);
        printf("/////////////////////////////////////////////\n");
        */
        
    }
    return n;
}



 
