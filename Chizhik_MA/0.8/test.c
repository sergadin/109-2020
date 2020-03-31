#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "../lib/umath.h"

#define EPS 1e-7
#define N 5

static double zero(double x) {
    	return 0 * x;
}

static double one(double x) {
    	return 0 * x + 1;
}

static double id(double x) {
    	return x;
}

static double sq(double x) {
    	return x * x;
}

static double cube(double x) {
	return x * x * x;
}

int main(void) {
    	double x[] = {3.56, 2};
    	dFUNC funcs[N] = {zero, one, id, sq, cube};
    	double *valArray,
	   	ansArray[][N] = {
				{0.0, 1.0, 3.56, 12.6736, 45.118016},
				{0.0, 1.0, 2.0, 4.0, 8.0}
			   };
	int m = (int)(sizeof(x) / sizeof(double));

    	for (int j = 0; j < m; j++) {
		valArray = getResults(funcs, N, x[j]);
		fprintf(stdout, "Test %d\n", j + 1);

		for (int k = 0; k < N; k++) {
			fprintf(stdout, "Test %d.%d\n", j + 1, k + 1);		    
		    	fprintf(stdout, "Result: %lf\n", valArray[k]);
		    	fprintf(stdout, "Expected answer: %lf\n", ansArray[j][k]);
		    
		    	if (compareDoubles(valArray[k], ansArray[j][k], EPS) == 0) {
		        	fprintf(stdout, "Test has been passed successfully.\n");
		    	} else {
		        	fprintf(stdout, "Something has gone wrong. Test has not been passed\n");
				free(valArray);
				return -1;
		    	}
		}
		fprintf(stdout, "Test %d has been passed\n", j + 1);
		free(valArray);
	}
	fprintf(stdout, "The program's output is correct. Everything's great\n");
    	return 0;
}
