#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"read_matr.h"
#include"prn_matr.h"
#include"solve.h"
#define Open_Err -1
#define Read_Err -2
#define All_Correct 1
#define Not_to_End -3
#define Err_of_Mem 2

//1.exe n matr.txt
int main(int argc,char **argv)
{
	int n;
	double t, res;
	char *File_Name = 0;
	double *a;
	
	if ((argc != 3) || !(n = atoi(argv[1])))
	{
		
		printf("Usage:%s n filename \n n - martix size \n filename - name of file with n * n numbers\n", argv[0]);
		return 1;
	}
	File_Name = argv[2];
	
	if (!(a = (double*) malloc (n*n*sizeof(double))))
	{
		printf("not enough memory\n");
		return 2;
	}
	
	if (File_Name)
	{
		int res = read_matr(a, n, File_Name);

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
			return 3;
		}
	}
	printf("Matrix A:\n");
	prn_matr(a, n);
	res = Inverse_matrix(a, n);
	if (res == Err_of_Mem) return 2;

	free(a);

	return 0;
}
