
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "1.h"
const double EPS = 1E-9;




void  rk (int n, int m, double **a)
{          
           int i,j,rank;
           for ( i = 0; i < n; i++ )
           {
           for ( j = 0; j < m; j++ )
              printf( "\t%10.3e", & a[i] [j] );
           printf("\n");
           }
           
           if (m>n) {rank=m;} else {rank=n;} 
           int *line_selected;
           line_selected = (int*)malloc(n * sizeof(int));

           for (int k=0; k<n; ++k) line_selected[k]=0;

         
           
           for ( i=0; i<m; ++i)
           {
               
               for (j=0; j<n; ++j)
                   if (!line_selected[j] && fabs(a[j][i]) > EPS)
                       break;
               if (j == n)
                   --rank;
               else
               {
                   line_selected[j] = 1;
                   for (int p=i+1; p<m; ++p)
                       a[j][p] /= a[j][i];
                   for (int k=0; k<n; ++k)
                       if (k != j && fabs (a[k][i]) > EPS)
                           for (int p=i+1; p<m; ++p)
                               a[k][p] -= a[j][p] * a[k][i];
               }
           }
             
    printf("rk = %d",rank);
}

