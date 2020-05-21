#include <stdio.h>
#include <stdlib.h>

#include "../libs/mystring/mystring.h"
#include "strings_words_symbols.h"

#define N 256

void sws(FILE *fin, FILE *fout)
{
	int swmf = 0, ces;
	/* swmf = Symbol_With_Max_Frequency;
	   ces = Count_of_Extra_Symbols*/
	struct result_of_counting answer;
	answer = count_sws(fin);
	switch(answer.ec)
	{
		case -1:
			{
				fprintf(fout, "Memory allocation error\n");
				break;
			}
		case -2:
			{
				fprintf(fout, "Unknown reading error\n");
				free(answer.symboltable);
				break;
			}
		case -3:
			{
				fprintf(fout, "Input file is empty\n");
				free(answer.symboltable);
				break;
			}
		default:
			{
				fprintf(fout, "Count of strings:        %d\n", answer.strc);
				fprintf(fout, "Maximum string's length: %d\n", answer.maxls);
				fprintf(fout, "Minimum string's length: %d\n", answer.minls);
				fprintf(fout, "Average string's length: %lf\n", (double)answer.symc/(double)answer.strc);
				fprintf(fout, "Count of words:        %d\n", answer.wc);
				fprintf(fout, "Maximum word's length:   %d\n", answer.maxlw);
				fprintf(fout, "Minimum word's length:   %d\n", answer.minlw);
				fprintf(fout, "Average word's length:   %lf\n", (double)(answer.symc - answer.symboltable[32].count)/(double)(answer.wc));
				fprintf(fout, "Count of symbols:        %d\n", answer.symc);
				for (int i = 0; i < N; i++)
				{
					if (answer.symboltable[i].count > swmf)
					{
						swmf = answer.symboltable[i].count;
					}
				}
				ces = decimal_places(swmf);
				for (int i = 0; i < N; i++)
				{
					if (answer.symboltable[i].count != 0)
					{
						fprintf(fout, "————————————————————————————————————————————————————————————————————————————————————————————————");
						for (int j = 0; j < (ces - 1); j++)
						{
							fprintf(fout, "—");
						}
						fprintf(fout, "\n| Symbol: ");
						if (answer.symboltable[i].symbol < 10)
						{
							if (answer.symboltable[i].symbol == 9)
							{
								fprintf(fout, "TAB | ASCII code   9");
							}
							else
							{
								fprintf(fout, " %c | ASCII code   %d", answer.symboltable[i].symbol, answer.symboltable[i].symbol);
							}
						}
						else
						{
							if (answer.symboltable[i].symbol < 100)
							{
								fprintf(fout, " %c  | ASCII code  %d", answer.symboltable[i].symbol, answer.symboltable[i].symbol);
							}
							else
							{
								fprintf(fout, " %c  | ASCII code %d", answer.symboltable[i].symbol, answer.symboltable[i].symbol);
							}
						}
						fprintf(fout, " | Occur with freauency %lf | Total symbols of such type: ", (double)answer.symboltable[i].count/(double)answer.symc);
						for (int j = 0; j < (ces - decimal_places(answer.symboltable[i].count)); j++)
						{
							fprintf(fout, " ");
						}
						fprintf(fout, "%d |\n", answer.symboltable[i].count);
					}
				}
				fprintf(fout, "————————————————————————————————————————————————————————————————————————————————————————————————");
				for (int j = 0; j < (ces - 1); j++)
				{
					fprintf(fout, "—");
				}
				free(answer.symboltable);
			}
	}
}

struct result_of_counting count_sws(FILE *fin)
{
	char *string;
	int cls, clw, pcis;
	/* cls = Current_Length_of_String,
	   clw = Current_Length_of_Word
	   pcis = Previous_Character_Is_Space*/
	struct result_of_counting result;
	result.ec = 0;
	result.strc = 0;
	result.wc = 0;
	result.symc = 0;
	if ((result.symboltable = (struct symbols_count*)malloc(N * sizeof(struct symbols_count))) == NULL)
	{
		result.ec = -1;
		return result;
	}
	for (int i = 0; i < N; i++)
	{
		result.symboltable[i].symbol = i;
		result.symboltable[i].count = 0;
	}
	while((string = sread(fin)) != NULL)
	{
		result.strc++;
		cls = slength(string);
		if (result.strc == 1)
		{
			result.minls = cls;
			result.maxls = cls;
			result.maxlw = 0;
			result.minlw = cls;
		}
		if (cls > result.maxls)
		{
			result.maxls = cls;
		}
		if (cls < result.minls)
		{
			result.minls = cls;
		}
		pcis = 0;
		clw = 0;
		for (int i = 0; i < cls; i++)
		{
			result.symboltable[string[i]].count++;
			switch(pcis)
			{
				case 0:
					{
						if (string[i] != ' ')
						{
							result.wc++;
							clw++;
							pcis = 1;
						}
						break;
					}
				case 1:
					{
						if (string[i] == ' ')
						{
							if (clw > result.maxlw)
							{
								result.maxlw = clw;
							}
							if (clw < result.minlw)
							{
								result.minlw = clw;
							}
							clw = 0;
							pcis = 0;
						}
						if (string[i] != ' ')
						{
							clw++;
							if (i == (cls - 1))
							{
								if (clw > result.maxlw)
								{
									result.maxlw = clw;
								}
								if (clw < result.minlw)
								{
									result.minlw = clw;
								}
							}
						}
						break;
					}
			}
		}
		result.symc += cls;
		free(string);
	}
	if (!feof(fin))
	{
		result.ec = -2;
	}
	if(result.strc == 0)
	{
		result.ec = -3;
	}
	return result;
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
