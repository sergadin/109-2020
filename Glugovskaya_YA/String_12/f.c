#include <string.h>
#include <stdio.h>
#include "f.h"

int Formating(const char *fileIn, const char *fileOut, int Start, int End)
{
	FILE *FileIn, *FileOut;
	char buf[LEN];
	int count = 1; 
	int Flag_paragraph = 0;
	
	if(!(FileIn = fopen(fileIn,"r")))
		return ERROR_OPEN_A;
	
	if(!(FileOut = fopen(fileOut,"w")))
		return ERROR_OPEN_B ;
	
	
	while (fgets(buf, LEN, FileIn))
	{
		if (count >= Start && count <= End)
		{
			if (buf[0] == '\n' && buf[1] == 0)
			{
				Flag_paragraph = 1;			
				
			}
			
			
			if (Flag_paragraph == 0 && buf[0] != '\n' && buf[1] != 0)
			{
				fprintf(FileOut, "%s", buf);
			}	
			
			if (Flag_paragraph == 1 && buf[0] != '\n' && buf[1] != 0)
			{
				fprintf(FileOut, "	");			
				fprintf(FileOut, "%s", buf);
				Flag_paragraph = 0;
			}		
		}	
		
		else 
		{
			fprintf(FileOut, "%s", buf);
		}
		count++;
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