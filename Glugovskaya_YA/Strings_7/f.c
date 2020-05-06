#include "f.h"

int Cut_Strings(const char *fileIn, const char *fileOut, int max_lenght)
{
	FILE *FileIn, *FileOut;
	char *buf;
	int *Count_El;
	int count = 0, i, t, j, Str = 0; 
	int Last_whitespace, Last_line_trans, FlagTBW = 0, Too_big_word = 0;
	int count_strings, lenght = 0;
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B;
	while((buf = Read_Srt(FileIn)) != NULL)
	{
		count = 0;
		Last_whitespace = -1;
		Last_line_trans = 0;
		FlagTBW = 0;
		lenght = strlen(buf);

		for (i = 0; buf[i]; i++)
		{
			count++;
			if (buf[i] == ' ')
			{			
				Last_whitespace = i;
			}

			if (count > max_lenght && (Last_whitespace > -1 && Last_whitespace > Last_line_trans))
			{
				if (buf[i+1] != '\n') 
					buf[Last_whitespace] = '\n';
				count = i - Last_whitespace;
				Last_line_trans = i;
				FlagTBW = 0;
			}
			
			if (count > max_lenght && Last_whitespace <= Last_line_trans && FlagTBW == 0)
			{
				Too_big_word +=1;
				FlagTBW = 1;
			}
		}
		
		fprintf(FileOut, "%s", buf);
		
		free(buf);
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



char *Read_Srt(FILE *FileIn)
{
	char buf[1024];
	char *s, *result = (char*) malloc (1 * sizeof(char));
	int len, count = 0;
	buf[0] = 0;
	
	s = fgets(buf, 1024, FileIn);

	if(s)
	{
		len = strlen(s);
		result = (char *) malloc((len + 1)*sizeof(char));
		strcpy(result, s);
		
		if (len < 1023) return result;
		
		while((s) && (s[strlen(s) - 1] != '\n'))
		{
			s = fgets(buf, 1024, FileIn);
			len += strlen(s);
        	result = (char *) realloc(result, len);
			strcat(result, s);		
		}
		return result;
	}
	free(s);
	free(result);
	return NULL;
}
