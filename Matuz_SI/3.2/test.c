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
    double Fmin, xmin;
    double a[] = {0, 0.5, 3.5, 0};
    double b[] = {12, 2, 10, 4};
    double m;

    for(int i = 0; i < n; i++)
    {
	Min_Search_Golden_Section(f[i], &a[i], &b[i], eps);
	printf("Test %d | local min is in (%.10lf; %.10lf)\n", i+1, a[i], b[i]);
	
        printf("f(a) = %.10lf \nf(b) = %.10lf  \n", (*f[i])(a[i]), (*f[i])(b[i]));
       
        if(((*f[i])(xmin) != (*f[i])(a[i])) && ((*f[i])(xmin) != (*f[i])(b[i])))
        {
	     xmin = parabolic_approx(a[i], (a[i]+b[i])/2, b[i], f[i]);
	}
	printf("     function's value is y = %.10lf \n", (*f[i])(xmin));
        printf("     function's argument is x = %.10lf \n", xmin);
        



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



