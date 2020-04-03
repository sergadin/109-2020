#include<stdio.h>
#include<math.h>

#include"2.h"

double f0(double x);
double f1(double x); 
double f2(double x); 
double f3(double x); 
double f4(double x); 


int main(void)
{
	int i;
	double a = -5;
	double b = 1;
	int N = 6;
//	double eps = 0.01;
	double result;
	double r_ans[] = {6,-42, -210 };
	RRFunc funcs[] = {f1, f3, f4};
	
	for(i = 0; i < 3; i++){

		result = solve2(a, b, N, funcs[i]);
		printf("правильный ответ:\n%lf\nответ:\n%lf\n%d трапеций/ии\n", r_ans[i], result, N);	
	}
}
double f0(double x) { 
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
