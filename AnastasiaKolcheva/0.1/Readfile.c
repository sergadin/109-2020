#include <stdio.h>
#include "array.h"


int main(void)
{
	int count, index;
	double value;
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

	for (index = 0; index < count; ++index)
	{
		value = func(arr[index]);
		printf("%d: f(%Lg) = %Lg\n", index, arr[index], value);
	}

	free(arr);

	fclose(finput);
}

