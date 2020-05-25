#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include <math.h>

 
static double f1(double x, double y) {
    	return 0;
}

static double f2(double x, double y) {
    	return 2*x + 3*y;
}

static double f3(double x, double y) {
    	return 4*x*y + 2*x + 5*y;
}

static double f4(double x, double y) {
    	return x * x * y;
}


int main(void) {
		int f =4, p = 4;
    	dFUNC mas_of_funcs[] = {f1, f2, f3, f4};
		double x[] = {1, 2, 3, 4};
		double y[] = {5, 6, 7, 8};
    	double *Answers; 
	   	double CorAns[4][4] = {{0.0, 0.0, 0.0, 0.0},{17.0, 22.0, 27.0, 32.0},{47.0, 82.0, 125.0, 176.0},{5.0, 24.0, 63.0, 128.0}};		
		Answers = (double*) malloc (p * sizeof(double));
		
    	for (int i = 0; i < f; i++) {
			Answers = func(mas_of_funcs[i], p, x, y);
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
