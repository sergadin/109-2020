#include <stdio.h>
#include <stdlib.h>

#include "strings_words_symbols.h"
#include "../libs/mystring/mystring.h"

int main(void)
{
	FILE *fin, *fout;
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Input file doesn't exist\n");
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		printf("Output file doesn't exist\n");
		fclose(fin);
		return -1;
	}
	sws(fin, fout);
	fclose(fin);
	fclose(fout);
	return 0;
}

