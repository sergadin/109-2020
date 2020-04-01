#include <stdio.h>
#include <math.h>
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

    for(int i = 0; i < n; i++)
    {
	Min_Search_Golden_Section(f[i], &a[i], &b[i], eps);
	printf("Test %d | local min is in (%.10lf; %.10lf)\n", i+1, a[i], b[i]);
	printf("     function's value is (%.10lf; %.10lf)\n", (*f[i])(a[i]), (*f[i])(b[i]));
	// а потом можно к интервалу применить штуку с параболой
	/*double parabolic_approx(RRfun f, double x1, double x2, double x3)
    {
        double approx;
        double F1 = (*f)(x1);
        double F2 = (*f)(x2);
        double F3 = (*f)(x3);
        approx = x2 - 0.5*((x2 - x1)*(x2 - x1)*(F2 - F3) - (x2 - x3)*(x2 - x3)*(F2 - F1))/((x2 - x1)*(F2 - F1) - (x2 - x1)*(F2 - F1));
        return approx;
    }
	 */
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