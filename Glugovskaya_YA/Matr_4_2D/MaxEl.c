#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include <math.h>
int MaxEl_In_Collon(double **a, int n, int m, int Pos)
{
	int i, j, Pos_MaxEl=0;
	double buf, maxel = a[Pos][Pos];
	
	for (i = Pos; i < n; i++)
	{
		
			if(fabs(a[i][Pos]) >= fabs (maxel)) {
				maxel = a[i][Pos];
				Pos_MaxEl = i;
			}
	}
	if ( Pos_MaxEl == Pos )	
	{
		return 1;
	}

	for (i = 0; i < m; i++)
	{
		buf = a[Pos_MaxEl][i];
		a[Pos_MaxEl][i] = a[Pos][i];
		a[Pos][i] = buf;
	}
	return -1;
}
