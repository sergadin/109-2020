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
    double eps = 0.000001;
    RRfun f[] = {f1, f2, f3, f4};
    double a[] = {0, 0.5, 3.5, -1};
    double b[] = {12, 2, 10, 2};
    double m;

    for(int i = 0; i < n; i++)
    {
	Min_Search_Golden_Section(f[i], &a[i], &b[i], eps);
	printf("Test %d | local min is in (%.10lf; %.10lf)\n", i+1, a[i], b[i]);
	printf("     function's value is y = %.10lf \n", (*f[i])(a[i]));
        /*m = parabolic_approx(a[i] - ????, b[i] + ????, (a[i]+b[i])/2, f[i]);
        printf("     function's argument is x = (%.10lf)\n", m);*/
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
{return (x*x*x*x - x);} // 0.62996, -0.47247