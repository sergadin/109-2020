#include"stdio.h"
#include"string.h"
#include"findstr.h"
#include"stdlib.h"




int main(void)
{
	FILE * input;
	char buf[5];
	char * prob;
	if((input = fopen("input", "r")) == NULL)
		return -1;
	prob = fgets(buf, 5, input);
	if(prob = NULL)
		return -1;
	findstr(prob, input);
	fclose(input);
	free(prob);
       	


}

