#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "findstr1.h"

int main(void)
{
	FILE *input, *output, *fdef;
	if((input = fopen("input.txt", "r")) == NULL)
	
		return -1;
	if((fdef = fopen("fdef.txt", "r")) == NULL)

                return -1;

	
	if((output = fopen("output.txt", "w")) == NULL)
	
		return -1;
	
	mainstrd(input, output, fdef);
	fclose(input);
	fclose(output);
	fclose(fdef);
	return 0;
}
