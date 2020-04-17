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

//1.exe n m matr.txt
int main(int argc,char **argv)
{
	int n, m, i, j;
	double t, res, det;
	char *File_Name = 0;
    
	if ((argc != 4) || !(n = atoi(argv[1])) || !(m = atoi(argv[2])))
	{
		
		printf("Usage:%s\n", argv[0]);
		return 1;
	}
	
	File_Name = argv[3];
	
	double **Matr_Equations = malloc(n * sizeof(double *));
	for (int row = 0; row < n; row++)
    {
        Matr_Equations[row] = malloc(m * sizeof(double));
    }
	
	if (File_Name)
	{
		int res = read_matr(Matr_Equations, n, m, File_Name);
		
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
			
			for (int row = 0; row < n; row++)
			{
				free(Matr_Equations[row]);
			}
			free(Matr_Equations);
			
			return 3;
		}
	}
	printf("Matrix A:\n");
	prn_matr(Matr_Equations, n, m);
	
	det = Stepped_View(Matr_Equations, n, m);
	printf("Det: %lf\n", det);	
	
	Return_Move(Matr_Equations, n, m);
	printf("\nCorrect answer:-1.615  1.153  -2.231  2\n");
	
	for (int row = 0; row < n; row++)
    {
        free(Matr_Equations[row]);
    }
	
    free(Matr_Equations);
	
	return 0;
}
