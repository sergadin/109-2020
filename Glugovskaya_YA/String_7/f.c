#include "f.h"

int Cut_Strings(const char *fileIn, const char *fileOut, int max_lenght)
{
	FILE *FileIn, *FileOut;
	char *buf;
	int *Count_El;
	int count = 0, i, t, j; 
	int Last_whitespace, Last_line_trans, FlagTBW = 0, Too_big_word = 0;
	int count_strings;
		
	count_strings = Count_Strings(fileIn);
	
	Count_El = (int*) malloc (count_strings * sizeof(int));
	Count_El_InString(fileIn, Count_El, count_strings);  
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B;
	
	for (t = 0; t < count_strings; t++)
	{
		buf = (char*) malloc (Count_El[t] * sizeof(char));
		for (j = 0; j < Count_El[t]; j++)
		{
			fscanf(FileIn, "%c", &buf[j]); 
		}

		count = 0;
		Last_whitespace = -1;
		Last_line_trans = 0;
		FlagTBW = 0;
		
		for (i = 0; i < Count_El[t]; i++)
		{
			count++;
	
			if (buf[i] == ' ')
				Last_whitespace = i;
	
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
		
		for (j = 0; j < Count_El[t]; j++)
			fprintf(FileOut, "%c", buf[j]);
		
		free(buf);
	}
	while (fscanf(FileIn, "%c", &buf[0]) == 1);
	
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

int Count_Strings (const char *fileIn)
{
	FILE *FileIn;
	char buf;
	int count_strings = 0;
	
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	while (fscanf(FileIn, "%c", &buf) == 1)
		if (buf == '\n')
			count_strings++;
	
	if(!feof(FileIn))
	{
		fclose(FileIn);
		return ERROR_READ_A;
	}
	fclose(FileIn);
	
	return count_strings;
}


int Count_El_InString(const char *fileIn, int *Count_El, int count_strings)
{
	FILE *FileIn;
	char buf;
	int i, count = 0;
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	for (i = 0; i < count_strings; i++)
	{	
		count = 1;
		fscanf(FileIn, "%c", &buf);
		
		while (buf != '\n' && count < MAX_IT)
		{
			fscanf(FileIn, "%c", &buf);
			count++;
		}
		Count_El[i] = count;
	}
	
	
	if(!feof(FileIn))
	{
		fclose(FileIn);
		return ERROR_READ_A;
	}
	fclose(FileIn);
	
	return 0;
}