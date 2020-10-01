#include <stdio.h>
#include <math.h>
#include "prot.h"
int task(RFun a, RFun b, double x){
    int i = 1;
    x = a(x);
    while(b(x) <= 0){
        x = a(x);
        i++;
        if(i > 1e7)
            return 0;
    }
    return i;//функция проверяет выполнение условия на функции для каждой последующей композиции, если проверок стало слишком много, считаем что условие не выполняется.
}
