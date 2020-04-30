#include <math.h>
#include <stdio.h>
#include "matr.h"
#include "invert_matrix.h"

int invert_matrix (int n, double *a, double *b)
{
    
    for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {                
                if(i==j)
                    b[i*n + j] = 1;
                else
                    b[i*n + j] = 0;
            }
        }
    
    for(int i = 0; i < n; i++)
    {
        double norm_a = norm_matrix(a, n);
        int max_i;
        if ( find_max_abs_redused_colum(n, a, i , &max_i) < 1e-16*norm_a )
        {
            return DETERMINANT_0;
        }
        //printf("imax=%d jmax=%d\n", max_i, max_j);
        if( max_i != i)
        {
            row_swap(a, n, n, max_i, i);
            row_swap(b, n, n, max_i, i);
        }
        for(int j = i+1; j < n ; j++)
        {
            a[i*n +j] /= a[i*n +i];;
        }
        
        
        for(int j = i+1 ; j < n; j++)
        {
            for(int k = i+1 ; k < n; k++)
            {
                a[j*n + k] -= a[i*n +k]*a[j*n + i];
            }
        
        }
        
        for(int j = 0; j <n ; j++)
        {
            b[i*n +j] /= a[i*n + i];
        }
        //a[i*n +i] /= a[i*n +i];
        for(int j = i+1 ; j < n; j++)
        {
            for(int k = 0 ; k < n; k++)
            {
                b[j*n + k] -= b[i*n +k]*a[j*n + i];
            }
           // a[j*n + i]  = 0;
        }
        /*
        printf("/////////////////////////////////////////////\n%d\n",i);
        print_matrix(a, n, n);
        printf("**\n");
        print_matrix(b, n, n);
        printf("/////////////////////////////////////////////\n");
        */
        
    }
    
    for(int i = n - 1; i > 0; i-- )
    {
        for(int j = 0; j < i; j++)
        {
            double temp = a[j*n + i];
            row_substr(b, n, n, i, j, temp);
        }
    }
    return OK;
}



 
