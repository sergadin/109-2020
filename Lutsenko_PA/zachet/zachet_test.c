#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zachet.h"




int main (void)


{
    int n;
    int m;
    FILE *input;
    
    if ((input = fopen("input.txt", "r")) == NULL)
    {
        printf("opening error");
        return 0;
    }
    
    fscanf(input, "%d", &n);
    fscanf(input, "%d", &m );
    
    
    double *syst = (double *)malloc(sizeof(double) * n * m);
    
    for ( int i = 0; i < n; i++ )
    for (int  j = 0; j < m; j++ )
      fscanf(input, "%lf",  &syst[i*(m)+j] );
    
    func(n, m, syst);
    
    
    fclose (input);
    
    free(syst);
    return 0;
    
    
    
}















