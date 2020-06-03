#include <stdio.h>
#include <stdlib.h>
#include "prn_matr.h"
#define MAX_PRN 20

void prn_matr(double*a,int n, int m)
{
  int i,j=0,N=(n>MAX_PRN?MAX_PRN:n), M=(m>MAX_PRN?MAX_PRN:m);
  
  for(i=0;i<N;i++)
  {
    for (j=0;j<M; j++){
    printf("%lf ",a[i*m+j]);
    if (j==M-1) printf("\n");
    }
    if (i==N-1)break;
    
  }
  
  printf("\n");
  
  return;
  
}