#include<stdio.h>
#include<math.h>

#include"2.h"

double f0(double x);
double f1(double x); 
double f2(double x); 
double f3(double x); 
double f4(double x); 
double si(double x);

int main(void)
{
	ErrorCode err;
	int i;
	double eps = 0.5;
	double a = -5;
	double b = 1;
	int N = 6;
	double result;
	double r_ans[] = {6,-42, -210, -1};
	RRFunc funcs[] = {f1, f3, f4, si};
	
	for(i = 0; i < 4; i++){
		result = integrate(a, b,eps, N, funcs[i], &err);
		if( err == INT_OK ) {
			printf("правильный ответ:\n%lf\nответ:\n%lf\n%d трапеций/ии\n", r_ans[i], result, N);	
			printf("меньше?=%d\n", fabs(r_ans[i] - result)/3 < eps);
		}
		else {
			printf("Error");
		}

}
}
double si(double x) {
	return sin(1/x);
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