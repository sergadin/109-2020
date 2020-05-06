#include <stdio.h>
#include <stdlib.h>

#include "../libs/mystring/mystring.h"
#include "words.h"

void symbols_words(FILE *fin, FILE *fout)
{
	char *string;
	int maxlen, minlen, curlen,  wc = 0, sc = 0; //wc = words_count sc = symbols_count;
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
		while ((string = sread(fin)) != NULL)
		{
			wc++;
			curlen = slength(string);
			if (wc == 1)
			{
				maxlen = curlen;
				minlen = maxlen;
			}
			sc += curlen;
			if (curlen > maxlen)
			{
				maxlen = curlen;
			}
			if (curlen < minlen)
			{
				minlen = curlen;
			}
			for (int i = 0; i < curlen; i++)
			{
				symboltable[string[i]].count++;
			}
			free(string);
		}
		if (!feof(fin))
		{
			printf("Unknown error\n");
		}
		else
		{
			if (wc == 0)
			{
				fprintf(fout, "Input file is empty\n");
			}
			else
			{
				if (wc == 1)
				{
					fprintf(fout, "There is only 1 word\n");
					fprintf(fout, "Its length is %d\n", maxlen);
					if (sc == 1)
					{
						fprintf(fout, "There is only 1 symbol\n:");
					}
					fprintf(fout, "There are %d symbols\n", sc);
				}
				else
				{
					fprintf(fout, "There are %d words:\n", wc);
					fprintf(fout, "String's maximum length is: %d\n", maxlen);
					fprintf(fout, "String's minimum length is: %d\n", minlen);
					avelen = ((double)sc)/((double)wc);
					fprintf(fout, "String's average length is: %lf\n", avelen);
					fprintf(fout, "There are %d symbols\n", sc);
				}
				for  (int i = 0; i < 256; i++)
				{
					if (symboltable[i].count != 0)
					{
						frequency = ((double)symboltable[i].count)/((double)sc);
						if (symboltable[i].symbol < 10)
						{
							fprintf(fout, "Symbol: %c ---- ASCII code: %d  ", symboltable[i].symbol, symboltable[i].symbol);
						}
						else
						{
							if(symboltable[i].symbol < 100)
							{
								fprintf(fout, "Symbol: %c ---- ASCII code: %d ", symboltable[i].symbol, symboltable[i].symbol);
							}
							else
							{
								fprintf(fout, "Symbol: %c ---- ASCII code: %d", symboltable[i].symbol, symboltable[i].symbol);
							}
						}
						fprintf(fout, " ---- Occure with frequency: %lf ---- Total symbols of such type: %d\n", frequency, symboltable[i].count);
					}
				}
			}
		}
		free(symboltable);
	}

}
