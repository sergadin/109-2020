#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include <math.h>
int MaxEl(double *a, int n, int Pos)
{
	int i, j, Pos_MaxEl=0;
	double *l;
	double buf, maxel = *(a + (Pos)*n + Pos);
	
	for (i = Pos; i < n; i++)
	{
		//printf("a[%d]=%lf %lf\n", i*n+Pos, a[i*n+Pos], maxel);
			if(fabs(*(a + i*n + Pos)) >= maxel) {
				//printf("%d\n", i);
				maxel = *(a + i*n + Pos);
				Pos_MaxEl = i;
			}
	}
	//printf("maxel:%lf %d %d\n", maxel, Pos_MaxEl, Pos);
	l=a+Pos_MaxEl*n;
	for (i = 0; i < n; i++)
	{
		//printf("a[%d]=%lf a[%d]=%lf\n", Pos_MaxEl*n+i, a[Pos_MaxEl*n+i], i+Pos*n, a[i+Pos*n]);
		buf = *(l+i);
		*(l+i) = *(a + i + Pos*n);
		*(a + i + Pos*n) = buf;
	}
	if ( Pos_MaxEl == Pos )	
	{
		return 1;
	}
	else 
		return -1;
	
}
