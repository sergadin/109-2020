#include<stdio.h>
#include<math.h>

#include"4.h"

#define pi 3.14159265358979323846

int main(void)
{
	int i;
	double r_res;
	double eps = 0.5;
	double result;
//	double co(double x);
	double x_mas[] = {pi/2 , 0, pi/3, pi/4 };
//	long double r_ans[] = {0.54030230586, 1, -0.53283302033, -0.66693806165};
//	double r_ans[] = {0,54, 1, −0,53, −0,66};
//	RRFunc funcs[] = {cos, cos, cos, cos};

		for(i = 0; i < 4; i++){
		r_res = cos(x_mas[i]);	
		result = Taylor_cos(x_mas[i], eps);
		printf("правильный ответ:\n%lf\nответ:\n%lf\n eps: %lf\n", r_res, result, eps);	
		printf("меньше?=%d\n", fabs(r_res - result) < eps);
		}

return 0;
}


