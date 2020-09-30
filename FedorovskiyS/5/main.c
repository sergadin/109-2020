#include <stdio.h>
#include <math.h>
#include "prot.h"
double f0(double x);
//double f1(double x);
//double f2(double x);

double g0(double x);
//double g1(double x);
//double g2(double x);

double f0(double x){
    return x+1;
}

/*double f1(double x){
    return x + 1; 
}*/

/*double f2(double x){
    return 2*x;
}*/

double g0(double x){
    return x*x - 100;
}

/*double g1(double x){
    return x - 100;
}*/

/*double g2(double x){
    return -1*x;
}*/

//тесты
int main(void){
    int i;
    double x = 1;
    i = task(f0, g0, x);//второй аргумент - функция которую сравниваем с нулем.
    printf("%d\n", i);
    return 0;
}

