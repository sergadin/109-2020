#include <stdio.h>
#include <stdlib.h>

#include "map.h"

#define EPS 1e-7
#define N 5

double modulus(double x);
double max(double *arr, int n);
int compareDoubles(double x1, double x2);


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
	int n, m;
	m = (int)(sizeof(x) / sizeof(double));

    for (int j = 0; j < m; j++) {
		valArray = getResults(funcs, N, x[j]);
		fprintf(stdout, "Test %d\n", j + 1);

		for (int k = 0; k < N; k++) {
			fprintf(stdout, "Test %d.%d\n", j + 1, k + 1);		    
		    fprintf(stdout, "Result: %lf\n", valArray[k]);
		    fprintf(stdout, "Expected answer: %lf\n", ansArray[j][k]);
		    
		    if (compareDoubles(valArray[k], ansArray[j][k]) == 0) {
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

double max(double *arr, int n) {
    double result = arr[0];
    if (n < 1) {
        return 0;
    }
    if (n == 1) {
        return result;
    }
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > result) {
            result = arr[i];
        }
    }
    
    return result;
}

double modulus(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

int compareDoubles(double x1, double x2) {
    double max_candidates[] = {1, x1, x2};
    if (modulus(x1 - x2) < EPS * max(max_candidates, 3)) {
        return 0;
    } else if (x1 > x2) {
        return 1;
    }
    return -1;
}
