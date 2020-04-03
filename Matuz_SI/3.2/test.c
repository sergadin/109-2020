#include <math.h>
#include <stdio.h>
#include "min.h"


double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);



int main(void)
{
    int n = 4;
    double eps = 0.1;
    RRfun f[] = {f1, f2, f3, f4};
    double Fa, Fb;
    double xmin;
    double a[] = {0, 0.5, 3.5, 0};
    double b[] = {12, 2, 10, 4};
    double m;

    for(int i = 0; i < n; i++)
    {
         printf("Test %d | ", i+1);
         min_with_strange_parabola_thing(f[i], a[i], b[i], eps);  
    }    
  

    return 0;
}


double f1(double x)
{return (x*x*x*x*x*x + 2*x*x*x - 7*x*x - 5*x);} // 1.17, -9.66 
double f2(double x)
{return (x*x*x*x*x*x*x*x - 10*x*x*x);} // 1.303, -13.813
double f3(double x)
{return (2/((x - 3)*(x - 3)) + x);}  // 4.5874, 5.3811
double f4(double x)
{return (x*x*x*x*x - 3*x*x*x*x + 5);} 



