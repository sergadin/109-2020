#include <stdio.h>
#include <math.h>
#include "pfunc.h"

int f1(int n, double x);
int f2(int n, double x);

int main(void) {
    double x[] = {1, 2, 3, 4};
	double eps = 0.0001;
	int n = sizeof(x)/sizeof(double), trueanswer[] = {8, 96}, answer;
	func funcs[] = {f1, f2};
    answer = convolution(x, n, f1);
	if(fabs(answer - trueanswer[0]) < eps)
        printf("%d\nok\n", answer);
    else
        printf("answer: %d\ntrue answer: %d \nsorry:(\n", answer, trueanswer[0]);
    answer = convolution(x, n, f2);
    if(fabs(answer - trueanswer[1]) < eps)
        printf("%d\nok\n", answer);
    else
        printf("answer: %d\ntrue answer: %d \nsorry:(\n", answer, trueanswer[1]);
}

int f1(int n, double x) {
	return n+1;
}
int f2(int n, double x) {
	return (int)n * x;
}
