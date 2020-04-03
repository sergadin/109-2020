#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sin.h"

int main(void)
{
	int* Error;
	double S;
	Error = (int*)malloc(1 * sizeof(int));

	printf("f(x) = sin(x)\n");

	S = Sin(0, 0.00001, Error);
	printf("x = 0, eps = 10^-5:\n");
	if (*Error)
		printf(" Error\n actual value:     %f\n", sin(0));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(0));

	S = Sin(1, 0.00001, Error);
	printf("x = 1, eps = 10^-5:\n");
	if (*Error)
		printf(" Error\n actual value:     %f\n", sin(1));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(1));

	S = Sin(10, 0.00001, Error);
	printf("x = 10, eps = 10^-5:\n");
	if (*Error)
		printf(" Error\n actual value:     %f\n", sin(10));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(10));

	/*S = Sin(100, 0.00001, Error);
	printf("x = 100, eps = 10^-5:\n");
	if (*Error)
		printf(" Error\n actual value:     %f\n", sin(100));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(100));*/

	S = Sin(100, 0.001, Error);
	printf("x = 100, eps = 10^-2:\n");
	if (*Error)
		printf(" Error\n actual value:     %f\n", sin(100));
	else
		printf(" calculated value: %f\n actual value:     %f\n", S, sin(100));

}