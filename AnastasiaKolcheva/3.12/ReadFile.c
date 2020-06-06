#include <stdio.h>
#include "replace.h"
#include "error.h"

void main(void)
{
	int error = format("file.in", "file.out", 40, 4);
	if (error == S_OK)
	{
		printf("results in file.out\n");
	}
	else
	{
		printf("error - %s (%d)\n", getErrorMessage(error), error);
	}
}