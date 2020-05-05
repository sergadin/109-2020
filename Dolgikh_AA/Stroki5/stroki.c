#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(void)
{
	FILE *input;
	int i;
	long int len;
	int *symbolstable;
	int words, minword, maxword, symbols;
	double average;
	
	symbolstable = (int *)malloc(256 * sizeof(int));
	for(i = 0; i < 256; i++)
		symbolstable[i] = 0;

	input = fopen("input.txt","r");
	

	FUNC(input, &words, &minword, &maxword, &symbols, symbolstable);
	average = (double)(symbols)/(double)(words);
	fprintf(stderr, "max: %d min: %d average: %g symbols/word\n", maxword, minword, average);
	for(i = 0; i < 256; i++)
	{
		if(symbolstable[i] != 0)
			fprintf(stdout, "symbol %c: %d times = %g percents\n", i, symbolstable[i], (double)symbolstable[i]/(double)symbols*100);
	}


	fclose(input);
	free(symbolstable);
	return 0;
}
