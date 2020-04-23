#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include <math.h>
int Raising_row_with_MaxEl_In_Collon(double *a, int n, int Pos)
{
	double *Start;
	double buf, maxel = *(a + (Pos)*n + Pos);
	int Pos_MaxEl = Pos;
	
	for (int i = Pos + 1; i < n; i++)
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
	for (int i = 0; i < n; i++)
	{
		//printf("a[%d]=%lf a[%d]=%lf\n", Pos_MaxEl*n+i, a[Pos_MaxEl*n+i], i+Pos*n, a[i+Pos*n]);
		buf = *(Start + i);
		*(Start + i) = *(a + i + Pos*n);
		*(a + i + Pos*n) = buf;
	}
	return -1;
}
