#include <stdio.h>
#include "func.h"
int proz(int a, int b);
int sum(int a, int b);

int main(void)
{
	int i, n = 4, result1 = 0, result2 = 0;
	int a[]={1, 2, 3, 4}, b[]={5, 6, 7, 8};
    	result1 = skal(a, b, n, sum, proz);
	result2 = skal(a, b, n, proz, sum);
	printf("%d\n", result1);
	printf("%d\n", result2);
	return 0;
}

int proz(int a, int b)
{
    return a*b;
}
int sum(int a, int b)
{
    return a+b;
}

