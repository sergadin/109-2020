#include <stdio.h>
#include "pfunc.h"

int convolution(double *x, int n, func f) {
	int answer = f(n, x[0]);
    for(int i = 1; i < n; i++) {
        answer = f(answer, x[i]);
    }
	return answer;
}
