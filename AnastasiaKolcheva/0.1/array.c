#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "array.h"

double func(double x)
{
	return (x * x * x);
}


void printArray(double* buffer, int count)
{
	int index;
	for (index = 0; index < count; ++index)
	{
		printf("x[%d] = %lg\n", index, buffer[index]);
	}
}

double* readArray(FILE* finput, int* count)
{
	int index;
	double* buffer;
	int temp;

	fscanf(finput, "%d", &temp);
	if (temp <= 0)
	{
		return NULL;
	}
	buffer = (double*)calloc(temp, sizeof(double));
	if (buffer == NULL)
	{
		return NULL;
	}
	for (index = 0; index < temp; ++index)
	{
		fscanf(finput, "%lg", &buffer[index]);
	}
	*count = temp;
	return buffer;
}