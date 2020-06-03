#include<stdio.h>
#include<math.h>

#include"3.h"
#define K (3 - sqrt(5)) / 2

double f1(double x); 
double f2(double x); 
double f3(double x); 
double f4(double x); 


int main(void)
{
	int i ;
	double eps = 1;
	double a = -5;
	double c = 1;
	ErrorCode error;
	double result;
	double r_ans[] = {-16 ,-51.028, -10.25, 11};
	RRFunc funcs[] = {f1, f2, f3, f4};
	
//double minimum(RRFunc f, double eps, double a, double b, ErrorCode *error)
	for(i = 0; i < 4; i++){
		result =  minimum(funcs[i], eps, a , c, &error);
			printf("правильный ответ:\n%lf\nответ:\n%lf\n eps: \n%lf\n", r_ans[i], result, eps);	
			printf("меньше?=%d\n", fabs(r_ans[i] - result) < eps);
		}

return 0;
}
double f1(double x) { 
	return x*x - 16;
}

double f2(double x) { 
	return x*x*x - 26*x;
}

double f3(double x) { 
	return x*x + 5*x - 4;
}

double f4(double x) { 
	return x*x - 6*x + 20;
}
