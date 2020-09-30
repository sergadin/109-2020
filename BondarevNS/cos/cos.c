#include<stdio.h>
#include<math.h>
#include"cos.h"

double Taylor(double x, double eps)
{
	double res = 1;
	double tay = 1;
	int n = 1;
	while ( fabs(tay) > eps )
{
		tay = (-1) * tay * x * x / (n * (n + 1));
		res = res + tay;
//		printf("tay : %lf\n res : %lf", tay, res);
		n += 2;
	}
return res;
}

