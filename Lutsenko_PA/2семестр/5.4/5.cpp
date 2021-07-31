#include <iostream>
#include "math.h"
#include "5.hpp"
using namespace std;

hermit::hermit(double *a,double *b,double *c,  int n)

{
    N = n;
    
    Z = new double[2*N];
    
    Q = new double * [2*N];
    for (int i = 0; i < 2*N; i++)
    {
        Q[i] = new double [2*N];
    }
    
    for (int i = 0; i <N; i++)
    {  
        Z[2*i] = a[i];
        Z[2*i+1] = a[i];
        Q[0][2*i] = b[i];
        Q[0][2*i+1]= b[i];
        Q[1][2*i+1]= c[i];
        if (i != 0)
            Q[1][2*i] = (Q[0][2*i] - Q[0][2*i-1]) / (Z[2*i] -Z[2*i-1]);
    }
    
    
   // for (int i = 0; i < 2*N; i++) std::cout<<Z[i]<<"  ";

    }


double hermit::Y(double XX)
{
 
   double S;
    int I,J;
    int K;
    
    // for (int i = 0; i < 2*N; i++) std::cout<<Z[i]<<"  ";
    
   K = 2 * (N-1)+ 1;
    
    for (I=2; I<=K; I++)
        for (J=2; J<=I; J++)
            Q[J][I] = ( Q[J - 1][I] - Q[J - 1][I - 1] ) / ( Z[I] - Z[I - J] );
     
        S = S = Q[K][K] * (XX - Z[K-1]);
    for (I=2; I<=K; I++) {
        J = K - I + 1;
        S = (S + Q[J][J]) * (XX - Z[J-1]);
    }
    S = S + Q[0][0];

        
   return S;
}



hermit::~hermit()
{
    delete [] Z;
    
    for (int i = 0; i < 2*N; i++)
        {
           delete [] Q[i];
        }
    delete [] Q;
    
}
