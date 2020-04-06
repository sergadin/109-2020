#include<stdio.h>
#include<stdlib.h>
#include"solve.h"
#include"test.h"
#define TooManyIT -1

int main(void)
{
	double a, b, e, x;
	int res;
	
	printf("input eps\n");
	
	if(scanf("%lf",&e) != 1)
	{
		printf("cannot read eps\n");
		return 2;
	}
	
	a = 0;
	b = 1;
	res = solve(a, b, e, &x, func);	
	if (res != TooManyIT)
	{
		printf("%lf)\n",  x);
	}
	
	res = solve(a, b, e, &x, func1);	
	if (res != TooManyIT)
	{
		printf("%lf)\n",  x);
	}
	
	res = solve(a, b, e, &x, func2);	
	if (res != TooManyIT)
	{
		printf("%lf)\n",  x);
	}
	
	return 0;
}