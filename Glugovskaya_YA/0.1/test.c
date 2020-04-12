#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include <math.h>

 
static double f1(double x) {
    	return 0;
}

static double f2(double x) {
    	return 2*x + 3;
}

static double f3(double x) {
    	return 4*x*x + 2*x + 5;
}

static double f4(double x) {
    	return x * x * x;
}


int main(void) {
		int f =4, p = 4;
    	dFUNC mas_of_funcs[] = {f1, f2, f3, f4};
		double x[] = {1, 2, 3, 4};
    	double *Answers; 
	   	double CorAns[4][4] = {{0.0, 0.0, 0.0, 0.0},{5.0, 7.0, 9.0, 11.0},{11.0, 25.0, 47.0, 77.0},{1.0, 8.0, 27.0, 64.0}};		
		Answers = (double*) malloc (p * sizeof(double));
		
    	for (int i = 0; i < f; i++) {
			Answers = func(mas_of_funcs[i], p, x);
			printf("\nМассив значений:");
			
			for (int j = 0; j < p; j++) {
				printf(" %lf", Answers[j]);
				}
				
			printf("\n Difference with correct:"); 
			
			for (int j = 0; j < p; j++) {
				printf(" %lf", fabs(Answers[j] - CorAns[i][j]));
				}
				
			printf("\n");	 
		}
		free(Answers);
    	return 0;
}
