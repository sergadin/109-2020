#include<stdio.h>
#include<stdlib.h>
#include"solve.h"
#include"test.h"
#define TooManyIT -1

void print (double res, double x)
{
	if (res != TooManyIT)
	{
		printf("%lf)\n",  x);
	}
}

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
	print(res, x);
	printf ("Correct answer on segment [0, 1]: (0, 0)\n");

	res = solve(a, b, e, &x, func1);	
	print(res, x);
	printf ("Correct answer on segment [0, 1]: (1, 0.514)\n");
	
	res = solve(a, b, e, &x, func2);	
	print(res, x);
	printf ("Correct answer on segment [0, 1]: (0.333, 4.667)\n");
	
	return 0;
}