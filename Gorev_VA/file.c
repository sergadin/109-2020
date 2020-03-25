#include <stdio.h>

double zero(double x);
double zero(double x)
{
	return 0*x;
}

int main(void)
{
	printf("%f", 1 + zero(4));
	return 0;
}