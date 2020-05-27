#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "read.h"
#include "print.h"
#include "solve.h"
#define Err_of_Mem 2

//1.exe n m matr.txt
int main(int argc,char **argv)
{
	int n, m;
	double t, res;
	char *File_Name = 0;
	char **a;
	
	if ((argc != 4) || !(n = atoi(argv[1])) || !(m = atoi(argv[1])))
	{
		printf("Usage:%s n m filename \n n m - martix size \n filename - name of file with n * n numbers\n", argv[0]);
		return -1;
	}
	File_Name = argv[3];
	
	if (!(a = (char**) malloc (n*m*sizeof(char*))))
	{
		printf("not enough memory\n");
		return -1;
	}
	
	if (File_Name)
	{
		int res = read(a, n, m, File_Name);

		if(res < 0)
		{
			switch(res)
			{
				case Open_Err:
				printf("Cannot open %s\n",File_Name);
				break;
				
				case Read_Err:
				printf("Cannot read %s\n",File_Name);
				break;
				
				case Not_to_End:
				printf("Not end of file %s\n",File_Name);
				break;
				
				default:
				printf("Uknown error %d in %s\n",res,File_Name);
			}
			
			free(a);
			return -1;
		}
	}
	printf("Matrix A:\n");
	print(a, n, m);
	solve(a, n, m);

	free(a);

	return 0;
}