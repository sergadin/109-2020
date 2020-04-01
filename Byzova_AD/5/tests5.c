#include<stdio.h>
#include<math.h>

#include"5.h"

double f1(double x);
double f2(double x); 
double f3(double x); 
double g1(double x); 
double g2(double x);
double g3(double x);


int main(void) {
	int i ;
	double x = 1;
	double result;
	double r_ans[] = {1 , 1 };
	RRFunc funcs[] = {f1, f2};
	RRFunc guncs[] = {g1, g2};
	for(i = 0; i < 2; i++){

		result = solve5(x, funcs[i], guncs[i]);
		printf("правильный ответ:\n%lf\nответ:\n%lf", r_ans[i], result);	
	}
}

double f1(double x) {
	return x;
}	
double f2(double x) {
	return - x*x + 1;
}	
//double f3(double x) {return ;}	
double g1(double x) {
	return x*x + 4;
}	
double g2(double x) {
	return x;
}	
//double g3(double x) {return ;}	

