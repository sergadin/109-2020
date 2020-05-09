#include <string.h>
#include <stdio.h>
#include "f.h"

int Formating(const char *fileIn, const char *fileOut, int max_len)
{
	FILE *FileIn, *FileOut;
	char *buf;
	int j, Del; 
	int Flag_paragraph = 0;
	int count = 0, Buf_len; 
	int Last_whitespace = -1, Last_line_trans = 0;
	char *Add;
	
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B;
	
	while((buf = Read_Srt(FileIn)) != NULL)
	{

		Del = Delete_whitespaces(buf);

	
		if ((int)(buf[0]) == 13 && (int)(buf[1]) == 10)
		{
			Flag_paragraph = 1;
			count = 0;
		}
		else
		{
			Last_line_trans = -1;
			Last_whitespace = 0;

			for (int i = 0; buf[i]; i++)
			{ 
				count++;
				if (buf[i] == ' ' || buf[i] == '\n')		
					Last_whitespace = i;


				if (count > max_len && (Last_whitespace > -1 && Last_whitespace > Last_line_trans))
				{
					if (buf[i+1] != '\n') 
						buf[Last_whitespace] = '\n';
					count = i - Last_whitespace;
					Last_line_trans = Last_whitespace + 1;
				}
				if ((i == (int)(strlen(buf) - 2)) && count < max_len)
				{
					if ((Add = Read_Srt(FileIn)) != NULL)
					{
						if (((int)(Add[0]) == 13 && (int)(Add[1]) == 10))
						{
							Flag_paragraph = 1;	
							break;
						}
						buf = (char *) realloc(buf, (strlen(Add)+strlen(buf)+1) * sizeof(buf));
						Buf_len = strlen(buf);
						
						buf[strlen(buf) - 2] = ' ';
						
						for (int j = Buf_len; j < (int)(strlen(Add)+Buf_len); j++)
						{
							buf[j-1] = Add[j - Buf_len]; 
						}
						
					}
				}
			}
		}
		if (Flag_paragraph == 0 && (int)(buf[0]) != 13 && (int)(buf[1]) != 10)
		{
			for (j = 0; j < (int)(strlen(buf) - Del); j++)
					fprintf(FileOut, "%c", buf[j]);
		}	
		
		if (Flag_paragraph == 1 && (int)(buf[0]) != 13 && (int)(buf[1]) != 10)
		{
			fprintf(FileOut, "	");			
			for (j = 0; j < (int)(strlen(buf)) - Del; j++)
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
	int len;
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