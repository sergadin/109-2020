#include <stdio.h>
#include <math.h>
#include "ln.h"
#define L2 0.69314718056//натуральный логарифм двойки.
//сначала пользуясь свойством умножения произведения и посчитанным логарифмом двойки свожу к области сходимости ряда тейлора, если нужно слишком много членов вывожу что есть, но предупреждаю о возможности плохого приближения.
double ln(double eps, double x, ErrCode *err){
    double sum = 0, plus, f = L2;
    int i;
    if((x < 0)||(fabs(x) < 1e-7)){
        if(err){
            *err = NO_RES;
        }
        return 0;
    }
    if(x >= 2){
        do{
            x = x/2;
            sum += L2;
        }while(x >= 2);
    }
    if(x < 1){
        do{
            x = x*2;
            sum -= L2;
        }while(x < 1);
    }
    plus = x-1;
    for(i = 1; 2*fabs(plus) > eps; ++i){
        sum += plus;
        plus *= -1*(x-1)*i;
        plus /= (i + 1);
        if(i > 1e7){
            if(err)
                *err = BAD_APR;
            return sum;
        }
    }
    if(err)
        *err = OK;
    return sum;
}
