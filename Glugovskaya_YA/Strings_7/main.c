#include "f.h"


//./1.exe n a.txt b.txt
int main(int argc, char **argv)
{
	int result, max_lenght;
	char *File_In, *File_Out;
	
	if ((argc!=4) || !(max_lenght = atoi(argv[1])))
	{
		printf("usage: %s.exe n a.txt b.txt \n n - lenght of string \n a.txt - input file \n b.txt - output file \n", argv[0]);
		return 1;
	}
	File_In = argv[2];
	File_Out = argv[3];
	
	result = Cut_Strings(File_In, File_Out, max_lenght);
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