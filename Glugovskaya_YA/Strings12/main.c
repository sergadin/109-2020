#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"


//./1.exe max_len a.txt b.txt
int main(int argc, char **argv)
{
	int result, max_len;
	char *File_In, *File_Out;
	
	if ((argc!=4) || !(max_len = atoi(argv[1])))
	{
		printf("usage: %s.exe n a.txt b.txt \n n - max lenght of string \n a.txt - input file \n b.txt - output file \n", argv[0]);
		return 1;
	}
	File_In = argv[2];
	File_Out = argv[3];
	
	result = Formating(File_In, File_Out, max_len);
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