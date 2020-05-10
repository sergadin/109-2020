#include <string.h>
#include <stdio.h>
#include "f.h"

int Formating(const char *fileIn, const char *fileOut, int max_len)
{
	FILE *FileIn, *FileOut;
	char *buf;
	int Flag_paragraph = 0, Start_w;
	int count_el = 0; 
	
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B;
	
	while((buf = Read_Srt(FileIn)) != NULL)
	{
		if ((int)(buf[0]) == 13 && (int)(buf[1]) == 10)
		{
			Flag_paragraph = 1;
			count_el = 0;
		}
		else{
			if (Flag_paragraph == 1)
			{
				fprintf(FileOut, "\n	");
				Flag_paragraph = 0;
			}
			
			for (int i = 0; buf[i]; i++)
			{
				Start_w = i;
				count_el++;
				while (buf[i] != ' ' && buf[i] != '\n' && buf[i] != 0 && (int)(buf[i]) != 13)
				{
					i++;
					count_el++;
				}
	
				if (count_el <= max_len)
				{
					for (int j = Start_w; j < i; j++)
							fprintf(FileOut, "%c", buf[j]);
		
					fprintf(FileOut, " ");
				}
			
				else 
				{
					fprintf(FileOut, "\n");
					fprintf(FileOut, 0);
					i = Start_w - 1;
					count_el = 0;
				}
			}	
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
