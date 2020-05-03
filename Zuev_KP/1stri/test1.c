#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "zamena.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);

int main(void)
{
	int i, j;
	double current;
	FILE *input1;
	if((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}

	return 0;
}


double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
