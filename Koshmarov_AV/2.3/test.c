#include <stdio.h>
#include "help.h"

#define count_f 3
#define left_border 2
#define right_border 4
#define N 1000000

double constanta (double x){
    return 5;
}

double line (double x){
    return 3*x + 1;
}

double square (double x){
    return x*x + 5*x + 6;
}

int main(){
    double ans;
    int helper = 0;
    int *buf = &helper;

    point_on_function arr_func[count_f] = {constanta, line, square};

    for (int i = 0; i < count_f; i++) {
        ans = simpson(*arr_func[i], left_border, right_border, N, buf);
        if (*buf != 0) {
            if (*buf == 1)
                printf("Введите четное число отрезков!");
            if (*buf == 2)
                printf("Пределы интегрирования введены неправильно!");
            continue;
        } else {
            printf("%.4lf\n", ans);
        }
        *buf = 0;
    }
    return 0;
}
