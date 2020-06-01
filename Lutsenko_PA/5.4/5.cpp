#include <iostream>
#include "5.hpp"

hermit::hermit(double *a1,double *b1,double *c1,double *d1,  int n)
{
    int N = n;
    
    a = (double*) malloc(n *sizeof(double));
    b = (double*) malloc(n *sizeof(double));
    c = (double*) malloc(n *sizeof(double));
    d = (double*) malloc(n *sizeof(double));
    

    for (int i = 0; i < N; i++)
    {  
        a[i] = a1[i];
        b[i] = b1[i];
        c[i] = c1[i];
        d[i] = d1[i];
    }
    
}


hermit::~hermit()
{
    free(a);
    free(b);
    free(c);
    free(d);
    
}



double hermit::Y(double XX)
{
 
   double YY, f_i_1, f_i;
    
   for(int i = 1; i < N; i++)
   {
       if ((a[i-1] <= XX) && (XX <= a[i]))
       {
           f_i_1 = (d[i-1]-c[i-1])/(b[i-1]-a[i-1]);
           f_i = (d[i]-c[i])/(b[i]-a[i]);
           
           YY = с[i-1] + (XX-a[i-1])*(f_i_1 + ((XX-a[i-1])*(f_i_1-(c[i-1]-c[i])/(a[i-1]-a[i])+(XX-a[i])*
                       (f_i_1-2*(c[i-1]-c[i])/(a[i-1]-a[i])+f_i)/(a[i-1]-a[i])))/(a[i-1]-a[i]));
               
       }
   }

   return YY;

}
