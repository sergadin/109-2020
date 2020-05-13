#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring/mystring.h"

#define TAB 8

void formatting(FILE *fin, FILE *fout, int mls)
{
	char *string;
	int ls, cls = 0, sc = 0, clw,  wc, wbi, wei, pcis, ec = 0, pshlz = 0;
	while((string = sread(fin)) != NULL)
	{
		sc++;
		ls = slength(string);
		wc = swc(string);
		if ((pshlz == 0) && (wc != 0))
		{
			cls = TAB;
			if (sc != 1)
			{
				fprintf(fout, "\n");
			}
			fprintf(fout, "\t");
		}
		pcis = 0;
		wbi = 0;
		wei = -1;
		for (int i = 0; i < wc; i++)
		{
			if (ec == -1)
			{
				break;
			}
			for (int j = (wei + 1); j < ls; j++)
			{
				switch(pcis)
				{
					case 0:
						if (string[j] != ' ')
						{
							wbi = j;
							pcis = 1;
							if (j == (ls - 1))
							{
								wei = j;
							}
						}
						break;
					case 1:
						if (string[j] == ' ')
						{
							wei = (j - 1);
							pcis = 0;
						}
						if ((string[j] != ' ') && (j == (ls - 1)))
						{
							wei = j;
						}
						break;
				}
				if (wei >= wbi)
				{
					break;
				}
			}
			clw = wei - wbi + 1;
			if ((clw > mls) || ((pshlz == 0) && (i == 0) && ((clw + cls) > mls)))
			{
				ec = -1;
			}
			else
			{
				if ((clw + 1) <= (mls - cls))
				{
					spw(wbi, wei, string, fout);
					fprintf(fout, " ");
					cls += (clw + 1);
				}
				else
				{
					if (clw == (mls - cls))
					{
						spw(wbi, wei, string, fout);
						if (i != wc)
						{
							fprintf(fout, "\n");
						}
						cls = 0;
					}
					else
					{
						fprintf(fout, "\n");
						spw(wbi, wei, string, fout);	
						if (clw == mls)
						{
							if (i != wc)
							{
								fprintf(fout, "\n");
							}
							cls = 0;
						}
						else
						{
							fprintf(fout, " ");
							cls = clw + 1;
						}
					}
				}
			}
			wbi = ls;
		}
		free(string);
		if (wc != 0)
		{
			pshlz = 1;
		}
		else
		{
			pshlz = 0;
		}
		if (ec == -1)
		{
			break;
		}
	}
	if (ec == -1)
	{
		fclose(fout);
		if ((fout = fopen("output.txt", "w")) == NULL)
		{	
			printf("Something went wrong\n");
		}
		else
		{
			fprintf(fout, "N is too short. Chenge input file or change N\n");
			fclose(fout);
		}
		fclose(fin);

	}
	else
	{
		fclose(fin);
		fclose(fout);
	}
}


void spw(int wbi, int wei, char *string, FILE *fout)
{
	for (int i = wbi; i <= wei; i++)
	{
		fprintf(fout, "%c", string[i]);
	}
}
