#include <stdio.h>
#include "simp.h"
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);

double f1(double x) {
	return 2 * x + 4;
}
double f2(double x) {
	return x * x * x + 27;
}
double f3(double x) {
	return cos(x / 10);
}

int main(void) {
    ErrorCode perr;
	double answer, a = 0, b = 1, eps = 0.001;
	double ideal[] = {5.0, 27.33333, 0.98158};
	RRfun fun[] = {f1, f2, f3};
	for(int i = 0; i < 3; i++) {
		answer = result(a, b, fun[i], &perr, eps);
        if(perr == I_OK)
		    printf("ideal:\n%f\nresult:\n%f\n", ideal[i], result);
        else if(perr == I_NOSEGM){
            printf("Sorry, non-exisment segment\n");
            return -1;
	    }
        else if(perr == I_FEW){
            printf("Sorry, too few segments\n");
            return -1;
	    }
        else if(perr == I_NO){
            printf("Sorry, don't converge\n");
            return -1;
	    }
	}
    return 0;
}

