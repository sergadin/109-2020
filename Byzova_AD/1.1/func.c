//tests

#include<stdio.h>
#include<math.h>

#include"func.h"

double f(double x);
double f1(double x); 
double f2(double x); 
double f3(double x); 
double f4(double x); 


int main(void)
{
	int i;
	double a = -5;
	double b = 1;
	double eps = 0.01;
	double result;
	double r_ans[] = {-3, 0 ,0.702, 0.246 };
	RRFunc funcs[] = {f1, f2, f3, f4};
	
	for(i = 0; i < 4; i++){

		result = solve1(a, b, eps, funcs[i]);
		printf("правильный ответ:\n%lf\nответ:\n%lf\nпогрешность%lf\n", r_ans[i], result, eps);	
	}
}

double f(double x) { 
	return x*x;
}

double f1(double x) { 
	return x + 3;
}

double f2(double x) { 
	return x*x - 2*x;
}

double f3(double x) { 
	return x*x + 5*x - 4;
}

double f4(double x) { 
	return x*x*x + 4*x - 1;
}



