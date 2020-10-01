#include "cos.h"
#include <math.h>
#include <stdio.h>

#define Max2(a,b) ((a)>(b) ? (a) : (b))
#define Max3(a,b,c) (Max2(Max2((a), (b)), (c)))


#define PI 3.14159265358979323846


//double cosine(double x, double eps)
int main(void)
{
    double result;
   
    double eps = 0.001;
    double x[] = {-PI/4, PI/2, 0, -11*PI/4, 81*PI/2, 0.001};
    int n = 6; // number of tests 
    double correct_value;
    double a;
    
    for (int i = 0; i < n; i++)
    {
	a = fmod(x[i], 2*PI);
        result = my_cosine(a, eps);
        correct_value = cos(a);	
	if ((module(result -correct_value)) < eps*Max3(result, correct_value, 1))
	{
	    printf("Test %d passed     |  ", i+1);
	    printf("cos %lf = % lf\n", x[i], result);
	}
	else
	    printf("Test %d failed     |  ", i+1);
	
    }
    /*
    for (int i = 0; i < n; i++)
    {
        x[i] = fmod(x[i], 2*PI);
        result = my_cosine(x[i], eps);
        printf("cos %lf = % lf\n", x[i], result);
    }
*/
    return 0;

}