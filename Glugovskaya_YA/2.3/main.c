#include<stdio.h> 
#include<stdlib.h>
#include"solve.h"
#include<math.h>
#include"test.h"
#define TooManyIT -1


int main (void)
{
	int n;
	double a, b, res, eps;
	
	printf("\nPlease enter \"n\": ");
	if(scanf("%d", &n) != 1)
	{
		printf("\nWrong input\n\n");
		return 0;
	}
	
	printf("\nPlease enter \"eps\": ");
	if(scanf("%lf", &eps) != 1)
	{
		printf("\nWrong input\n\n");
		return 0;
	}
	a = 1.2;
	b = 2;
	res = solve(f, a, b, n, eps);
	
	if (res != TooManyIT)
	{
		printf("\nres = %lf\n\n", res);
	}
	else 
	{
		printf ("\n Too Many Iterations\n");
	}
	
	
	a = 0.3;
	b = 1;
	res = solve(f1, a, b, n, eps);
	
	if (res != TooManyIT)
	{
		printf("\nres = %lf\n\n", res);
	}
	else 
	{
		printf ("\n Too Many Iterations\n");
	}

	return 0;
}

