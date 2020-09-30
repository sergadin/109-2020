#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prog1-0.h"

#define famount 5
#define namount 4

double zero(double x){
    return 0*x;
}

double linear(double x){
    return x + 1;
}

double square(double x){
    return x*x + 5;
}

double arctg(double x){
    return atan(x);
}

double tgh(double x){
	return tanh(x);
}

int main(){

    fpointer f[famount] = {zero, linear, square, arctg, tgh};
    double arguments[namount] = {0, 3, -5.54, 11000};
    double correct_ans[famount][namount] = {0, 0, 0, 0, 1, 4, -4.54, 11001, 5, 14, 35.6916, 121000005, 0, 1.249046, -1.392214, 1.570705, 0, 0.995055, -0.999969, 1};
    double *res_mas = NULL;

    for (int i = 0; i < famount; i++){
        res_mas = result(*f[i], arguments, namount);
        printf("Test for function #%d:\n", i + 1);
        for (int j = 0; j < namount; j ++) {
            if(fabs(res_mas[j] - correct_ans[i][j]) <= eps)
                printf("Test #%d completed\n", j + 1);
            else {
                printf("Test #%d failed!\n", j + 1);
		printf("Your answer is %lf \n", res_mas[j]);
		printf("The correct answer is %lf \n", correct_ans[i][j]);
                return 0;
            }
        }
    }

    printf("\n");
    printf("All tests completed successfully\n");
    free(res_mas);
    return 0;
}
