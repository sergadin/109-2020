#include <string.h>
#include <stdio.h>
#include "f.h"

int Formating(const char *fileIn, const char *fileOut, int max_len)
{
	FILE *FileIn, *FileOut;
	char *buf;
	int j, Del; 
	int Flag_paragraph = 0;
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B;
	
	while((buf = Read_Srt(FileIn)) != NULL)
	{
		Del = Delete_whitespaces(buf);
		Max_Size_String(buf, max_len);
	
		if ((int)(buf[0]) == 13 && (int)(buf[1]) == 10)
			Flag_paragraph = 1;				
		
		if (Flag_paragraph == 0 && (int)(buf[0]) != 13 && (int)(buf[1]) != 10)
		{
			for (j = 0; j < (strlen(buf) - Del); j++)
					fprintf(FileOut, "%c", buf[j]);
		}	
		
		if (Flag_paragraph == 1 && (int)(buf[0]) != 13 && (int)(buf[1]) != 10)
		{
			fprintf(FileOut, "	");			
			for (j = 0; j < strlen(buf) - Del; j++)
					fprintf(FileOut, "%c", buf[j]);
			Flag_paragraph = 0;
		}
		free(buf);		
	}
	
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

void Max_Size_String(char *buf, int max_len)
{
	int count = 0; 
	int Last_whitespace = -1, Last_line_trans = 0;
		
	for (int i = 0; buf[i]; i++)
	{
		count++;
		if (buf[i] == ' ')
		{			
			Last_whitespace = i;
		}

		if (count > max_len && (Last_whitespace > -1 && Last_whitespace > Last_line_trans))
		{
			if (buf[i+1] != '\n') 
				buf[Last_whitespace] = '\n';
			count = i - Last_whitespace;
			Last_line_trans = i;
		}
	}
}
 
int Delete_whitespaces(char *buf)
{
	int count = 0;
	for (int i = 1; buf[i]; i++)
	{ 
		if (buf[i-1] == ' ' && buf[i] == ' ')
		{ 
			count++;
			for (int j = i; buf[j]; j++)
			{
				buf[j-1] = buf[j];
			}
			i--;
		}
	}
	
	return count;
}