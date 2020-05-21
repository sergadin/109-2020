#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "change.h"

int main(void)
{
	FILE *input;
	size_t size_buffer = 32;
	char **data = malloc(size_buffer * sizeof(char *)), old[] = "ot", curr[] = "ooooot";
	int size_array = 0;

	if ((input = fopen("input.txt", "r")) == NULL) 
	{
		printf("ERROR open input\n");
		return -1;
	}
	read_file(input, data, &size_array, size_buffer);

	if(curr != NULL)
	{
		for (int i = 0; i < size_array; i++)
		{
			change(data[i], old, curr);
		}
	}
	printf("\n");

	for (int i = 0; i <= size_array; i++)
	{
		free(data[i]);
	}
	fclose(input);
	free(data);
	return 0;
}
