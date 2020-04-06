#include <iostream>
#include "5.hpp"

hermit::hermit(double *a,double *b,double *c,  int n)
{
    int N = n;
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < N; i++)
    {
        x[i] = a[i];
        y[i] = b[i];
        z[i] = c[i];
    }
    
}


hermit::~hermit()
{
    free (x);
    free (y);
    
}



double hermit::Y(double XX)
{
   double Q[2*N][2*N],Z[N];
   double S;
   int I,J,K;
   
      for (I=0; I<=N; I++) {
         
         Z[2*I] = x[I];
         Z[2*I+1] = x[I];
         Q[2*I+1][0] = y[I];
         Q[2*I+1][1] = z[I];
         
         if (I != 0)
            Q[2*I][1] = (Q[2*I][0] - Q[2*I-1][0]) / (Z[2*I] -Z[2*I-1]);
      }
   K = 2 * N + 1;
      for (I=2; I<= 2 * N + 1; I++)
         for (J=2; J<=I; J++)
            Q[I][J] = ( Q[I][J - 1] - Q[I - 1][J - 1] ) / ( Z[I] - Z[I - J] );
      
     
         S = Q[K][K] * (XX - Z[K-1]);
         for (I=2; I<=K; I++) {
            J = K - I + 1;
            S = (S + Q[J][J]) * (XX - Z[J-1]);
         }
         S = S + Q[0][0];
        
   return S;
}
