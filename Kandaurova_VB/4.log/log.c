#include <stdio.h>
#include "log.h"

double mod(double x) {
	if(x < 0)
		return -x;
	else
		return x;
}

double taylor(double x, double eps) { 
	int step = 0, k = 2;
	double result = 0, answer = x;
	while((mod(answer) > eps)&&(step < 10000)) {
		result += answer;
		answer *= (-1) * x * (k - 1) / k;
		k++;
		step++;
	}	
	return result;
}