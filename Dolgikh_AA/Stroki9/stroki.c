#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(void)
{
	char *filelist = malloc(2 * sizeof(char));
	
	filelist[0] = 32;
	filelist[1] = 0;

	char *input_file_name = "input.txt";
	FILE *output;

	if((output = fopen("result.txt", "w")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		return -1;
	}

	filelist = include(output, input_file_name, filelist);

	fclose(output);

	free(filelist);

	return 0;
}
