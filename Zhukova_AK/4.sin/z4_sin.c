#include <stdio.h>
#include <math.h>
#include "z4_sin.h"
//эта фунция вычисляет sinx с точностью до некоторого eps

double sinx (double x, double eps)
{
	double t = x;
	double s = 0;
	int k = 0;

        while (fabs(t) >= eps)
        {
		s = s + t;
		k = k + 2;
			t = -(t*x*x)/(k*(k+1));

//		printf("x=%f\n", t);
        }

        return s;

}




