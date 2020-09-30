#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_SIZE 1024

int main() 
{
	char **filelist = malloc(1 * sizeof(char *));
	int listlength = 0;
	char *filename = "input.txt";
	FILE *output;
	filelist[0] = NULL;
	if((output = fopen("result.txt","w")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		return -1;
	}
	filelist = include(output, filename, filelist, &listlength);

	fclose(output);
	
	free(filelist);


	return 0;
}
