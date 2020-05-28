#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "indent.h"

int main(void)
{
	FILE *input, *output;
	int max_len = 50;

	if ((input = fopen("input.txt", "r")) == NULL)
	{
		printf("ERROR open input\n");
		return -1;
	}

 	if ((output = fopen("output.txt", "w")) == NULL)
        {
                printf("ERROR open output\n");
		fclose(input);
                return -1;
        }
	
	indent(input, output, max_len);

	return 0;
}
