#include "integral.h"
#include <stdio.h>
#define Max2(a,b) ((a)>(b) ? (a) : (b))
#define Max3(a, b, c) Max2(Max2((a), (b)), (c))
double module(double x)
{
    if(x < 0)
        x = -x;
    return x;
}


double integration(RRfun f, double a, double b, int n)
{
    double h;
    double x;
    double integral;
    double sum = 0;
    int i;
    h = module(b-a)/n;
    for(i = 1; i < n; i++)
    {
        x = a + i*h;
        if( i % 2 == 0)
        {
            sum += 2*((*f)(x));
        }
        else
        {
            sum += 4*((*f)(x));
        }
        
    }
    integral = (h/3)*(((*f)(a)) + ((*f)(b)) + sum);
    


    // https://en.wikipedia.org/wiki/Simpson%27s_rule
    return integral;
}



struct answer simpsons_integration(RRfun f, double a, double b, double eps)
{
    double integral, new_integral;
    int n = 2;
    struct answer ans;
    new_integral = integration(f, a, b, n);
    //printf("%lf", new_integral);
    do
    {        
        integral = new_integral;
        n *= 2;
        //printf("%lf", new_integral);
        new_integral = integration(f, a, b, n);
        //printf("%lf", new_integral);

	if (n > 10000000) // какое здесь должно быть ограничение?
	{
	    n = -1;
	    break;
	}

    }while(module(new_integral-integral)>=eps*Max3(new_integral, integral, 1));
    printf("%d", n);

    ans.integral = new_integral;
    
    ans.n = n;
    //printf("%d", ans.n);

    return ans;
}