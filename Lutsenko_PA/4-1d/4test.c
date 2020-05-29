#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "4.h"




int main (void)


{
    int n;
    FILE *input;
    if ((input = fopen("input.txt", "r")) == NULL)
    {
        printf("opening error");
        return 0;
    }
    fscanf(input, "%d", &n);
    double *answ = (double *)malloc(sizeof(double) * n);
    double *syst = (double *)malloc(sizeof(double) * n * (n+1));
    
    for ( int i = 0; i < n; i++ )
    for (int  j = 0; j < n + 1; j++ )
      fscanf(input, "%lf",  &syst[i*(n+1)+j] );
    
    gauss(n, syst, answ);
    
    
    fclose (input);
    free(answ);
    free(syst);
    return 0;
    
    
    
}















