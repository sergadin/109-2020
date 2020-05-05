#include <string.h>
#include <stdio.h>
#include "f.h"

int Formating(const char *fileIn, const char *fileOut, int Start, int End)
{
	FILE *FileIn, *FileOut;
	char *buf;
	int *Count_El;
	int count = 1, count_strings, i, j, t; 
	int Flag_paragraph = 0;
	
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
			fscanf(FileIn, "%c", &buf[j]); 

		if (count >= Start && count <= End)
		{
			if ((int)(buf[0]) == 13 && (int)(buf[1]) == 10)
				Flag_paragraph = 1;				
			
			if (Flag_paragraph == 0 && (int)(buf[0]) != 13 && (int)(buf[1]) != 10)
			{
				for (j = 0; j < Count_El[t]; j++)
					fprintf(FileOut, "%c", buf[j]);
			}	
				
			if (Flag_paragraph == 1 && (int)(buf[0]) != 13 && (int)(buf[1]) != 10)
			{
				fprintf(FileOut, "	");			
				for (j = 0; j < Count_El[t]; j++)
					fprintf(FileOut, "%c", buf[j]);
				Flag_paragraph = 0;
			}		
		}	
		
		else 
			for (j = 0; j < Count_El[t]; j++)
				fprintf(FileOut, "%c", buf[j]);
		count++;
		
	}
		
	while (fscanf(FileIn, "%c", &buf[0]) == 1);

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