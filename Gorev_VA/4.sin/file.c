#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include "sin.h"

#define eps 0.0000001

int main(void)
{
	int* Error;
	double S;
	Error = (int*)malloc(1 * sizeof(int));

	printf("f(x) = sin(x)\n");

	S = Sin(0, eps, Error);
	printf("x = 0:\n");
	if (*Error)
		printf(" Error\n actual value:     %f", sin(0));
	else
		prinf(" calculated value: %f\n actual value:     %f", , sin(0));

	S = Sin(1, eps, Error);
	printf("x = 1:\n");
	if (*Error)
		printf(" Error\n actual value:     %f", sin(1));
	else
		prinf(" calculated value: %f\n actual value:     %f", , sin(1));

	S = Sin(100, eps, Error);
	printf("x = 100:\n");
	if (*Error)
		printf(" Error\n actual value:     %f", sin(100));
	else
		prinf(" calculated value: %f\n actual value:     %f", , sin(100));

}