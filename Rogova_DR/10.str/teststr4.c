#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "findstr.h"

int main(void)
{
	FILE *input, *output, *fdef;
	if((input = fopen("input.txt", "r")) == NULL)
	
		return -1;
	if((input = fopen("fdef.txt", "r")) == NULL)

                return -1;

	
	if((output = fopen("output.txt", "w")) == NULL)
	
		return -1;
	
	ch_fl_wth_def(input, output, fdef);
	fclose(input);
	fclose(output);
	return 0;
}
