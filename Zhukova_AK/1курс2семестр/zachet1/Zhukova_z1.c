#include <stdio.h>
#include "Zhukova_z1.h"
#include  <string.h>
//находит номер строки, подходящей под условие
//затем удаляет "лишние" символы из строк
void funcMass (int m, int n, char ** mass)
{
	int row1, row2, res, col, len1, len11, len2, i, j, k, help;
//	char buf;
	res = -5;
//	printf ("p1\n");
	for (row1=0; row1<m; row1++)
	{
		for (row2=row1+1; row2<m; row2++)
		{
			len1 = 0;
			len2 = 0;
			for (col=0; col<n; col++)
			{
				len1 = strlen(mass [m*row1 + col]) + len1;
				len2 = strlen(mass [m*row2 + col]) + len2;
			}
//printf ("r1=%d r2=%d col=%d l1=%d l2=%d\n", row1, row2 ,col, len1, len2);			}
			if ((len1 == len2) && (res < 0))
			{
	//			len1= len1 -n;
	//			len2= len2 - n;
				for (i=0; i<len1/2; i++)
				{
					if ((mass[m*row1 +i])[0] == (mass[m*row2+len1/2-i-1])[0])
					{
						res = row1;
					}
					else
					{
						res = -3;
					}
//				printf ("m1=%c m2=%c\n", (mass[row1*m+i])[0],(mass[row2*m+len1-i-1])[0]);
//					printf ("m1=%c m2=%c\n", (mass[m*row1+i])[0],(mass[m*row2+len1/2-1-i])[0]);
//					printf ("res=%d\n", res);
				}
			}
		}
	}
//	printf ("p2\n");
	if (res >= 0)
	{
		for (row1=0; row1<m; row1++)
		{
			for (col=0; col<n; col++)
			{
				len1 = strlen (mass[m*row1+col]);
				len2 = strlen (mass[m*res+col]);
				len11 = len1;
				for (i=0; i<len1; i++)
				{
					for (j=0; j<len2; j++)
					{
//						printf ("p3\n");
						if (mass[m*row1+col][i] == mass[m*res+col][j])

						{
							help = help + 1;
						}
					}
					if (help == 0)
					{
						for (j=0; j<len1; j++)
						{
							if (mass[m*row1+col][i] == mass[m*row1][j])
							{
								len11 = len11 - 1;
								for (k=j; k<len11; k++)
								{
									mass[m*row1][k] = mass[m*row1][k+1];
								}
								mass[m*row1][len1-1] = 0;
							}
						}
					}
				}
			}
		}
//				if (char *strchr(char *mass[m*row1+col],int (mass[m*row1]+i))== NULL)
	}
}
