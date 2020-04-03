#include <math.h>
#include <stdio.h>
#include "decision.1.1.h"

#define max(a, b) (((a) > (b))?(a):(b))
#define MAX(a, b, c) max(a, max(b, c))
#define E 0.0000001

double linear(double x);
double square(double x);
double zero(double x);
int main(void)
{
	int i, num = 3;
	double result, X_1 = -2, X_2 = 3;
	double true_answer[] = {0, 2, 0};
	ErrorCode ec;
	RRF funcs[] = {linear, square, zero};
	for(i = 0; i < num; i++)
	{
		result = dcsn_f_x(X_1, X_2, E, funcs[i], &ec);
                
		if(ec != SF_OK)
		{
			printf("ERROR test %d\n", i+1);
		}

		else
		{
			printf("true: %lf real: %lf+-%lf\n", true_answer[i], result, E);
			if (fabs(result - true_answer[i]) > E*MAX(1, result, true_answer[i]))
			{
				printf("incorrect test %d\n", i+1);
			}
		}	
	}

	return 0;
}

double linear(double x)
{
	return x;
}

double square(double x)
{
	return x*x + x - 6;
}

double zero(double x)
{
	return 0;
}
