#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zachet.h"

void  func (int n, int m, double *syst)
{         
    double currsum=0;
    double maxsum=0;
    int strnum=0;
    double currscalar=0;
    
    for ( int i = 0; i < n; i++ )
    {
         currsum=0;
        
        for (int  j = 0; j < m; j++ )
           {
              if  (abs(syst[i*m]>syst[i*(m)+j])) {currsum=currsum+syst[i*(m)+j];}
           }
        
        if (currsum>maxsum)
            {maxsum=currsum;
                strnum=i;
            }
            
    }
    
    
    for ( int i = 0; i < n; i++ )
    {
        for (int  j = 0; j < m; j++ )
        {
            for (int  k = j; k < m; k++ ) {currscalar=currscalar+syst[i*m+k]*syst[strnum*m+k];}
            syst[i*(m)+j]=currscalar;
            currscalar=0;
        }
            
    }
    
    for ( int i = 0; i < n; i++ )
    {
      for (int  j = 0; j < m; j++ )
         {
           printf( "%.1f\t",  syst[i*(m)+j] );
          }
       printf( "\n");
    }
    
    }



