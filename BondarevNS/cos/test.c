#include<stdio.h>
#include<math.h>
#include"cos.h"
#define pi 3.14

int main(void)
{
	int i;
	double r_res;
	double eps = 0.5;
	double result;
	double x_mas[] = {pi/2 , 0, pi/3, pi/4 };

		for(i = 0; i < 4; i++){
		r_res = cos(x_mas[i]);	
		result = Taylor_cos(x_mas[i], eps);
		printf("правильный ответ:\n%lf\nответ:\n%lf\n eps: %lf\n", r_res, result, eps);	
		printf("меньше?=%d\n", fabs(r_res - result) < eps);
		}

return 0;
}

