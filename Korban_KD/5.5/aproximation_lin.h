#include <math.h>

using namespace std;

typedef double (*dndFUNC)(double x);
#define PRECITION 1e-16


class aproximation_lin
{
private:
    double k;
    double b;
public:
    int aprox(dndFUNC f, double *x, int n)
    {
        double a01 = 0, a11 = 0, b0 = 0, b1 = 0;
        for(int i = 0; i < n; i++)
        {
            a01 += x[i];
            a11 += x[i] * x[i];
            b0 += f(x[i]);
            b1 += f(x[i]) * x[i];
        }
        
        if( fabs( n * a11 - a01 * a01) > PRECITION )
        {
            k = (n * b1 - b0 * a01) / ( n * a11 - a01 * a01);
            b = (b0 * a11 - a01 * b1) / ( n * a11 - a01 * a01);
            return 0;
        }
        else
        {
            return -1;
        }
    }
    double get_k()
    {
        return k;
    }
    double get_b()
    {
        return b;
    }
    double get_value(double x)
    {
        return k * x + b;
    }
};
