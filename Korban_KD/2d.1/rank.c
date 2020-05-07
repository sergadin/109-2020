#include <math.h>
#include <stdio.h>
#include "matr.h"
#include "rank.h"

int rank_matrix (double **a ,int n, int m)
{
    double norm_a = norm_matrix(a, n, m);
    int h = fmin(n,m);
    for(int i = 0; i < h; i++)
    {
        
        int max_i, max_j;
        //printf("/////////////////////////////////////////////\n%d\n",i);
        if ( find_max_abs_redused(n, m, a, i , &max_i, &max_j) < 1e-16*fmin(1,norm_a) )
        {
            return i;
        }
        //printf("imax=%d jmax=%d\n", max_i, max_j);
        if( max_i != i)
        {
            double *temp= a[i];
            a[i] = a[max_i];
            a[max_i] = temp;
        }
        
        if( max_j != i)
        {
            for(int k = 0; k < n; k++)
            {
                double temp = a[k][i];
                a[k][i] = a[k][max_j];
                a[k][max_j] = temp;
            }
        }
        
        //print_matrix(a, n, n);
        //printf("\n");
        
        for(int j = i + 1 ; j < m ; j++)
        {
            a[i][j] /= a[i][i];;
        }
        a[i][i] = 1;
        
        for(int j = i+1 ; j < n; j++)
        {
            double temp = a[j][i];
            for(int k = i ; k < m; k++)
            {
                a[j][k] -= a[i][k]*temp;
            }
            
        }
        
        
        //print_matrix(a, n, n);
        //printf("/////////////////////////////////////////////\n");
        
    }
    return h;
}



 
