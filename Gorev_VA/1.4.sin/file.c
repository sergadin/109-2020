#include <stdio.h>
#include <math.h>
#include "sin.h"

int main(void)
{
	ErrorCode E;
	double S;

	printf("f(x) = sin(x)\n");

	S = Sin(0, 0.000001, E);
	printf("x = 0, eps = 10^-6:\n");
	if (E == ERROR_OF_INT)
		printf(" Error\n actual value:     %f\n", sin(0));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(0));

	S = Sin(1, 0.000001, E);
	printf("x = 1, eps = 10^-6:\n");
	if (E == ERROR_OF_INT)
		printf(" Error\n actual value:     %f\n", sin(1));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(1));

	S = Sin(10, 0.000001, E);
	printf("x = 10, eps = 10^-6:\n");
	if (E == ERROR_OF_INT)
		printf(" Error\n actual value:     %f\n", sin(10));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(10));

	S = Sin(-10, 0.000001, E);
	printf("x = -10, eps = 10^-6:\n");
	if (E == ERROR_OF_INT)
		printf(" Error\n actual value:     %f\n", sin(-10));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(-10));

}
