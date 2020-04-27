#include <string.h>
#include <stdio.h>
#include "f.h"

int Cut_Strings(const char *fileIn, const char *fileOut, int max_lenght)
{
	FILE *FileIn, *FileOut;
	char buf[LEN];
	int count = 0; 
	int lenght; 
	int Last_whitespace, Last_line_trans, FlagTBW = 0, Too_big_word = 0;
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B ;
	
	
	while (fgets(buf, LEN, FileIn))
	{
		lenght = strlen(buf);
		count = 0;
		Last_whitespace = -1;
		Last_line_trans = 0;
		FlagTBW = 0;
		for (int i = 0; buf[i]; i++)
		{
			count++;
			//printf("count: %d i: %d %c\n", count, i, buf[i]);
			if (buf[i] == ' ')
			{
				Last_whitespace = i;
				//printf("buf[%d]=%c\n", i, buf[i]);
			}
	
			if (count > max_lenght && (Last_whitespace > -1 && Last_whitespace > Last_line_trans))
			{
				//printf("Count %d:\n", count);
				if (buf[i+1] != '\n') 
					buf[Last_whitespace] = '\n';
				count = i - Last_whitespace;
				Last_line_trans = i;
				FlagTBW = 0;
				//printf("Buf: %s\n", buf);
			}
			
			if (count > max_lenght && Last_whitespace <= Last_line_trans && FlagTBW == 0)
			{
				//printf("i: %d \n", i);
				Too_big_word +=1;
				FlagTBW = 1;
			}
		}
		fprintf(FileOut, "%s", buf);
	}
	
	if (Too_big_word != 0)
		printf ("There are %d words that are too large, please, choose a longer string length\n", Too_big_word);
	
	
	if(!feof(FileIn))
	{
		fclose(FileIn);
		fclose(FileOut);
		return ERROR_READ_A;
	}
	fclose(FileIn);
	fclose(FileOut);
	
	return 0;
}