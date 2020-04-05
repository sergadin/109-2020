#include "exp.h"
#include <math.h>
#include <stdio.h>

#define max(a,b) ((a)>(b) ? (a) : (b))
#define MAX(a,b,c) (max(max((a), (b)), (c)))
#define PI 3.14159265358979323846
#define E 0.000001
int main(void)
{
    double a, result, true_value;
    int n = 5;
    double A[] = {0, 1, -4, PI, 5.6};  
    
    for (int i = 0; i < n; i++)
    {
	a = A[i];
        result = EXPON(a, E);
        true_value = exp(a);

	printf("true: %lf real: %lf+-%lf\n", true_value, result, E);
	if (fabs(result - true_value) > E * MAX(1, result, true_value))
	{
		printf("incorrect test %d\n", i+1);
	}
    }
    
    return 0;

}
