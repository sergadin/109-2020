#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include <math.h>
int MaxEl_In_Collon(double *a, int n, int Pos)
{
	int i, j, Pos_MaxEl=0;
	double *Start;
	double buf, maxel = *(a + (Pos)*n + Pos);
	
	for (i = Pos; i < n; i++)
	{
		
			if(fabs(a[ i*n + Pos]) >= fabs (maxel)) {
				maxel = a[i*n + Pos];
				Pos_MaxEl = i;
			}
	}
	if ( Pos_MaxEl == Pos )	
	{
		return 1;
	}
	//printf("maxel:%lf %d %d\n", maxel, Pos_MaxEl, Pos);
	Start = a+Pos_MaxEl*n;
	for (i = 0; i < n; i++)
	{
		//printf("a[%d]=%lf a[%d]=%lf\n", Pos_MaxEl*n+i, a[Pos_MaxEl*n+i], i+Pos*n, a[i+Pos*n]);
		buf = *(Start + i);
		*(Start + i) = *(a + i + Pos*n);
		*(a + i + Pos*n) = buf;
	}
	return -1;
}
