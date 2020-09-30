#include <stdio.h>
#include <math.h>
#include "ln.h"

int main(void){
    ErrCode err;
    //double x = exp(1);//ответ: 1
    double x = 2;//ответ: 0.69314718056
    //double x = 1;//ответ: 0
    double eps = 1e-6, sum;
    sum = ln(eps, x, &err);
    switch(err){
        case NO_RES:
            printf("invalid argument!\n");
            return -1;
        case BAD_APR:
            printf("bad approximation is possible!\n");
            break;
    }
    printf("%lf\n", sum);
    return 0;
}

