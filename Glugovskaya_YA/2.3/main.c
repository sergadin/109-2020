#include "f.h"

int main (void)
{
	int n;
	double a, b, res;
	
	printf("\nPlease enter \"a\": ");
	if(scanf("%lf", &a) != 1)
	{
		printf("\nWrong input\n\n");
		return 0;
	}
	
	printf("\nPlease enter \"b\": ");
	if(scanf("%lf", &b) != 1)
	{
		printf("\nWrong input\n\n");
		return 0;
	}
	
	printf("\nPlease enter \"n\": ");
	if((scanf("%d", &n) != 1) || (n < 1))
	{
		printf("\nWrong input\n\n");
		return 0;
	}
	
	//printf("\nn = %d\n\n", n);
	res = solve(f, a, b, n);
	
	printf("\nres = %lf\n\n", res);
	
	return 0;
}

