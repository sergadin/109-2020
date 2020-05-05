#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "findstr.h"

int main(void)
{
	FILE *input, *output;
	if((input = fopen("input.txt", "r")) == NULL)
	
		return -1;
	
	if((output = fopen("output.txt", "w")) == NULL)
	
		return -1;
	
	findstr(input, output, "k");
	fclose(input);
	fclose(output);
	return 0;
}
