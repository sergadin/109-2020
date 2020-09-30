#include <stdio.h>
#include <math.h>
#include "integral.h"
double f1(double x);
double f2(double x);
double f3(double x);
double f(double x);

int main(void) {
    //int n = 3; // number of tests
    double eps = 0.000001;
    struct answer ans;

    /*double a[] = {3, 10, 1};
    double b[] = {9, 12, 2};
    RRfun f[] = {f1, f2, f3};
    for (int k = 0; k < n; k++)
    {
        ans = simpsons_integration(f[k], a[k], b[k], eps);
        if (ans.n == -1)
        {
	    printf("did not want to integrate this thing\n ");
        }
        else
    	    printf("Test %d | integral =  %lf\n ", k, ans.integral);
    }*/

    
    ans = simpsons_integration(f, eps, 1, eps);
    if (ans.n == -1)
    {
	printf("did not want to integrate this thing\n ");
    }
    else
    printf("Test | integral =  %lf\n ", ans.integral);


    return 0;
}

double f(double x)
{return sin(1/x);} // res: 0.504067


double f1(double x)
{return x*x;} // res: 234

double f2(double x)
{return 0*x;}// res: 0

double f3(double x)
{return x;}// res: 3/2



