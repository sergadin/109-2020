#include <iostream>
#include <stdlib.h>
#include "aproximation_lin.h"

double f1(double x)
{
    return 2*x +1; 
}

double f2(double x)
{
    return 10 * x + 10;
}

double f3(double x)
{
    return 5 * x + 20;
}

double f4(double x)
{
    return x*x*x;
}

int main()
{
    aproximation_lin data;
    int n = 100, res;
    double *x;
    double left = -10, right = 10, h = (right - left)/n, x0 = 5;
    
    dndFUNC foo[] = {f1, f2, f3, f4};
    double k[] = {2, 10, 5};
    double b[] = {1, 10, 20};
    
    
    if( !(x = (double *)malloc(n*sizeof(double)) ) )
    {
        printf("memory error\n");
        return -1;
    }
    
    for(int i = 0; i < n; i++)
    {
        x[i] = left + i*h;
    }
    
    cout << "test on linear functions" << "\n\n";
    
    for (int i = 0; i < 3; i++)
    {
        res = data.aprox(foo[i], x, n);
        if(res < 0)
        {
            printf("determinat was too small unable to solve\n");
        }
        else
        {
            cout << "resul: linear function " << data.get_k() << "x + " << data.get_b() << "\n";
            cout << "actual linear function " << k[i] << "x + " << b[i] << "\n";
            cout << "resul: value in f("<< x0 <<")=" << data.get_value(x0) << "\n";
            cout << "actual value in f("<< x0 <<")=" << foo[i](x0) << "\n\n";
        }
    }
    
    cout << "test on some function (x^3)" << "\n";
    
    res = data.aprox(f4, x, n);
        if(res < 0)
        {
            printf("determinat was too small unable to solve\n");
        }
        else
        {
            cout << "resul: linear function "<<data.get_k() << "x + " << data.get_b() << "\n";
            cout << "resul: value in f("<< x0 <<")=" <<data.get_value(x0) << "\n";
        }
    return 0;
    
}

