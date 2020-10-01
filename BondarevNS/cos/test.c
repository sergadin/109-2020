#include<stdio.h>
#include<math.h>
#include"cos.h"
#define pi 3.141592653589

int main(void)
{
	int i;
	double r_res;
	double eps = 0.000005;
	double res;
	double x[] = {pi/2 , 0, pi/3, pi/4 };
	for(i = 0; i < 4; i++)
{
		r_res = cos(x[i]);	
		res = Taylor(x[i], eps);
		printf("correct:\n%lf\nmy:\n%lf+-%lf\n", r_res, res, eps);	
}
	return 0;
}

