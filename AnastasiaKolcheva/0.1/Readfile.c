#include <stdio.h>
#include <stdlib.h>
#include "array.h"


int main(void)
{
	int count;
	double* arr;

	FILE* finput = fopen("array.txt", "r");
	if (finput == NULL)
	{
		printf("cannot open file\n");
		return 1;
	}

	arr = readArray(finput, &count);
	if (arr == NULL)
	{
		printf("out of memory\n");
		return 1;
	}

	printArray(arr, count);

	for (int index = 0; index < count; ++index)
	{
		double f = func(arr[index]);
		printf("%d: f(%lg) = %lg\n", index, arr[index], f);
	}

	free(arr);

	fclose(finput);
}

