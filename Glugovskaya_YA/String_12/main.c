#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"


//./1.exe Start End a.txt b.txt
int main(int argc, char **argv)
{
	int result, Start, End;
	char *File_In, *File_Out;
	
	if ((argc!=5) || !(Start = atoi(argv[1])) || !(End = atoi(argv[2])))
	{
		printf("usage: %s.exe Start End a.txt b.txt \n Start and End - Start and end of the formatting interval \n a.txt - input file \n b.txt - output file \n", argv[0]);
		return 1;
	}
	File_In = argv[3];
	File_Out = argv[4];
	
	result = Formating(File_In, File_Out, Start, End);
	if(result < 0)
	{
		switch(result)
		{
			case ERROR_OPEN_A:
			printf("cannot open a");
			case ERROR_OPEN_B:
			printf("cannot open b");
			case ERROR_READ_A:
			printf("cannot read a");
			default:
			printf("unknown ERROR");
		}
		return 2;
	}

	return 0;
}