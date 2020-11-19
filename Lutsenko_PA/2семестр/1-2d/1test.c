#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "1.h"





int main (void)


{
    int n,m;
     
    FILE *input;
    if ((input = fopen("input.txt", "r")) == NULL)
    {
        printf("opening error");
        return 0;
    }
    
    fscanf(input, "%d", & n);
    fscanf(input, "%d", & m );
    
    double **syst = (double**)malloc(sizeof(double *) * n);
    for (int row = 0; row < n; row++)
    {
        syst[row] = (double*)malloc(m * sizeof(double));
    }
    
    for (int i = 0; i < n; i++ )
    for (int j = 0; j < m; j++ )
      fscanf(input, "%lf", &(syst[i] [j]) ); 

    

    rk(n,m,syst);
    
   for (int row = 0; row < n; row++)
   {
       free(syst[row]);
   }
   free(syst);
    
    fclose (input);
    return 0;
    
    
    
}















