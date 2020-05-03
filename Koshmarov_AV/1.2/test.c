#include <stdio.h>
#include "help.h"

#define eps 1e-7
#define root_of -3.26346444

double f (double x){
    return x*x*x + 4*x*x + 7*x + 15;
}

double f_fpr (double x){
    return 3*x*x + 8*x + 7;
}

double f_spr (double x){
    return 6*x + 8;
}

int main(){

    double roots;
    double a = -3.5;
    double b = -3;
    char *check;
    *check = 1;
    roots = root(f, f_fpr, f_spr, a, b, check);
    if (*check == 1)
        if (roots - root_of > eps)
            printf("Test failed!\nYour program is bad!");
        else
            printf("%.8lf\n\nTest completed!\nYour program is good!", roots);
    else
        printf("На данном отрезке нет корня!");

    return 0;
}
