#include <stdio.h>
#include <stdlib.h>

#include "../libs/mystring/mystring.h"
#include "strings_words_symbols.h"

void count_sws(FILE *fin, FILE *fout)
{
	char *string, check;
	int maxls, minls, cls, maxlw, minlw, clw, strc = 0 , wc = 0, symc = 0, swmf = 0, ces = 0;
	/*maxls = MAXimum_Length_of_String, minls = MINimum_Length_of_String,
	  cls = Current_Length_of_String, maxlw = MAXimum_Length_of_Word,
	  minlw = MINimum_Length_of_Word, clw = Current_Length_of_Word
	  strc = STRings_Count, wc = Words_Count, symc = SYMbols_Count,
	  swmf = Symbol_With_Max_Frequency, ces = Count_of_Extra_Symbols*/
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
		while((string = sread(fin)) != NULL)
		{
			strc++;
			cls = slength(string);
			if (strc == 1)
			{
				minls = cls;
				maxls = cls;
				maxlw = 0;
				minlw = cls;
			}
			if (cls > maxls)
			{
				maxls = cls;
			}
			if (cls < minls)
			{
				minls = cls;
			}
			check = 0;
			clw = 0;
			for (int i = 0; i < cls; i++)
			{
				symboltable[string[i]].count++;
				switch(check)
				{
					case 0:
						{
							if (string[i] != ' ')
							{
								wc++;
								clw++;
								check = 1;
							}
							break;
						}
					case 1:
						{
							if (string[i] == ' ')
							{
								if (clw > maxlw)
								{
									maxlw = clw;
								}
								if (clw < minlw)
								{
									minlw = clw;
								}													
								clw = 0;
								check = 0;
							}
							if (string[i] != ' ')
							{
								clw++;
								if (i == (cls - 1))
								{
									if (clw > maxlw)
									{
										maxlw = clw;
									}
									if (clw < minlw)
									{
										minlw = clw;
									}
								}
							}
							break;
						}
				}
			}
			symc += cls;			
			free(string);
		}
		if (!feof(fin))
		{
			fprintf(fout, "Unknown error\n");
		}
		else
		{
			if(strc == 0)
			{
				fprintf(fout, "Input file is empty\n");
			}
			else
			{
				fprintf(fout, "Count of strings:        %d\n", strc);
				fprintf(fout, "Maximum string's length: %d\n", maxls);
				fprintf(fout, "Minimum string's length: %d\n", minls);
				fprintf(fout, "Average string's length: %lf\n", (double)symc/(double)strc);
				fprintf(fout, "Count of strings:        %d\n", wc);
				fprintf(fout, "Maximum word's length:   %d\n", maxlw);
				fprintf(fout, "Minimum word's length:   %d\n", minlw);
				fprintf(fout, "Average word's length:   %lf\n", (double)(symc - symboltable[32].count)/(double)(wc));
				fprintf(fout, "Count of symbols:        %d\n", symc);
				for (int i = 0; i < 256; i++)
				{
					if (symboltable[i].count > swmf)
					{
						swmf = symboltable[i].count;
					}
				}
				ces = decimal_places(swmf);
				for (int i = 0; i < 256; i++)
				{
					if (symboltable[i].count != 0)
					{
						fprintf(fout, "————————————————————————————————————————————————————————————————————————————————————————————————");
						for (int j = 0; j < (ces - 1); j++)
						{
							fprintf(fout, "—");
						}
						fprintf(fout, "\n");
						if (symboltable[i].symbol < 10)
						{
							if (symboltable[i].symbol == 9)
							{
								fprintf(fout, "| Symbol: TAB | ASCII code   9");
							}
							else
							{
								fprintf(fout, "| Symbol:  %c  | ASCII code   %d", symboltable[i].symbol, symboltable[i].symbol);
							}
						}
						else
						{
							if (symboltable[i].symbol < 100)
							{
								fprintf(fout, "| Symbol:  %c  | ASCII code  %d", symboltable[i].symbol, symboltable[i].symbol);
							}
							else
							{
								fprintf(fout, "| Symbol:  %c  | ASCII code %d", symboltable[i].symbol, symboltable[i].symbol);
							}
						}
						fprintf(fout, " | Occur with freauency %lf | Total symbols of such type: ", (double)symboltable[i].count/(double)symc);
						for (int j = 0; j < (ces - decimal_places(symboltable[i].count)); j++)
						{
							fprintf(fout, " ");
						}
						fprintf(fout, "%d |\n", symboltable[i].count);
					}
				}
				fprintf(fout, "————————————————————————————————————————————————————————————————————————————————————————————————");
				for (int j = 0; j < (ces - 1); j++)
				{
					fprintf(fout, "—");
				}
			}
		}
		free(symboltable);
	}
}

int decimal_places(int number)
{
	int count = 1, factor = 10;
	while ((number / factor) != 0)
	{
		count++;
		factor *= 10;
	}
	return count;
}
