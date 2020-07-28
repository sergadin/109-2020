#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prog3-0.h"

#define argamount 4
#define famount 5

int zero (int n, double x){
    return 0*x;
}

int add_floor(int n, double x){
	int low = floor(x);
	return low + n;
}

int add_ceil(int n, double x){
	int high = ceil(x);
    return high+n;
}

int mult_floor(int n, double x){
	int low = floor(x);
	return low*n;
}

int mult_ceil(int n, double x){
	int high = ceil(x);
    return high*n;
}

int main(){
	int res, n, i, j;
	n = 1;
    fpointer f[famount] = {zero, add_floor, add_ceil, mult_floor, mult_ceil};
    double arguments[argamount] = {1, 3, -5.54, 11000};

    for (int i = 0; i < famount; i++){
        res = fold(*f[i], arguments, n, argamount);
        printf("Test for function #%d:", i + 1);
        printf("%d \n", res);
    }

    printf("\n");
    printf("All tests completed successfully\n");
    return 0;
}
