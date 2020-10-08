#include<stdio.h> 
#include<stdlib.h>
#include"solve.h"
#include<math.h>
#include"test.h"
#define TooManyIT -1
#define CantFind -2

int main(void)
{
	double a, b, e, x, corAn;
	int res;
	
	
	printf("input eps\n");
	
	if (scanf("%lf", &e) != 1)
	{
		printf("cannot read eps\n");
		return 2;
	}
	
	
	a = 0;
	b = 5;
	res = solve(a, b, e, &x, func1);
	
	if ((res != TooManyIT) || (res != CantFind))
	{
		printf("\nИтерации=%d Корень=%lf\n", res, x);
	}
	
	corAn = 2.143973;
	printf("DIFFERENCE: %lf\n", corAn - x);
	
	
	res = solve(a, b, e, &x, func);	
	if ((res != TooManyIT) || (res != CantFind))
	{
		printf("\nИтерации=%d Корень=%lf\n", res, x);
	}
	corAn = 1.70977; 
	printf("DIFFERENCE:%lf\n", corAn - x);
	

	a = -1;
	b = 0;
	res = solve(a, b, e, &x, func2);
	if ((res != TooManyIT) || (res != CantFind))
	{
		printf("\nИтерации=%d Корень=%lf\n", res, x);
	}
	corAn = -0.337571;
	printf("DIFFERENCE:%lf\n", corAn - x);
	
	
	a = 0;
	b = 1;
	res = solve(a, b, e, &x, func3);
	if ((res != TooManyIT) || (res != CantFind))
	{
		printf("\nИтерации=%d Корень=%lf\n", res, x);
	}
	corAn = 1;
	printf("DIFFERENCE:%lf\n", corAn - x);
	return 0;
}