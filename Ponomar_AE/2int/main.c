#include <stdio.h>
#include <math.h>
#include "2int.h"
double func(double X_2);
double f(double t);
#define max(a, b) (((a) > (b))?(a):(b))
#define MAX(a, b, c) max(a, max(b, c))

int main(void)
{
	int i;
	double ep = 0.0001, X_1 = 0, X_2 = 20, result = 0;
	double e = 0.1;
	double true_answer[] = {3.997};
	ErrorCode ec;
	RRFUN1 funcs[] = {func};
	for(i = 0; i < 1; i++)
	{
		result = dcsn_f_x(X_1, X_2, ep, funcs[i], &ec);	
		if (fabs(result - true_answer[i]) < e*MAX(result, true_answer[i], 1))
		{
			printf("OK\n");
			printf("%lf\n", result);
		}
		else
		{
			printf("ERROR TEST\n");
			printf("%lf\n", result);
		}
	}

	return 0;
}

double func(double X_2)
{
	double ep = 0.00001, X_1 = 0, alpha = 6;
	return integral(X_1, X_2, ep, f) - 1 - 0.1*alpha;
}

double f(double t)
{
	return (1/(sqrt(1+t*t*t*t)));
}
