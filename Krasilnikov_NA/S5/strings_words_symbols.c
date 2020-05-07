#include <stdio.h>
#include <stdlib.h>

#include "../libs/mystring/mystring.h"
#include "strings_words_symbols.h"

void count_sws(FILE *fin, FILE *fout)
{
	char *string;
	int maxls, minls, cls, maxlw, minlw, clw, strc = 0 , wc = 0, symc = 0;
	/*strc = STRings_Count, wc = Words_Count, symc = SYMbols_Count,
	maxls = MAXimum_Length_of_String, minls = MINimum_Length_of_String,
	cls = Current_Length_of_String, maxlw = MAXimum_Length_of_Word,
	minlw = MINimum_Length_of_Word, clw = Current_Length_of_Word*/
	double avelen, frequency;
	struct symbols_count *symboltable;
	if ((symboltable = (struct symbols_count*)malloc(256 * sizeof(struct symbols_count))) == NULL)
	{
		fprintf(fout, "Memory allocation error");
	}
	else
	{
		for (int i = 0; i < 256; i++)
		{
			symboltable[i].symbol = i;
			symboltable[i].count = 0;
		}
		free(symboltable);
	}
}
