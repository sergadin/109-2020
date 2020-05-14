#include "help.h"

double simpson(point_on_function f, double a, double b, int n, int *buff_err){

    if (n % 2 == 1) {    // Проверяем, чтобы число отрезков было четным
        *buff_err = 1;
        return 0;
    }

    if (a > b){         // Проверям, в том ли порядке расположены пределы
        *buff_err = 2;
        return 0;
    }

    double step = (b - a) / n;  //Сам метод Симпсона
    double integral = 0;
    int count = 0;

    while (count < n){
        if (count % 2 == 1)
            integral += 4*(*f)(a + count*step);
        else
            integral += 2*(*f)(a + count*step);
        count++;
    }

    integral += (*f)(a) + (*f)(b);
    integral *= (b - a)/(3*n);
    return integral;
}
