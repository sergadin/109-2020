#include <stdio.h>
#include <math.h>
#include "min.h"
double min(RFun f, double eps, double a, double b, ErrCode *err){//программа перебирает разбиения уменьшая разность, пока не найдет i удовлетворяющее неравенству на локальный минимум на множествее точек разбиения, и рассматривает новый отрезок с его соседями по разбиению на концах. Когда отрезок стал маленьким, исчем вершину параболы и значение от нее. если i не находится, выводим число заведомо больше чем значение на концах. для этого не требуется запоминать изначальные концы, т.к. нахождения одного i достаточно для гарантии нахождения минимума.
    double dx = (b - a)/4;
    int i = 0, n = 4, minflag = 0;
    while(dx > 1e-7){
        while(i < n){
            if(f(a + i*dx) > f(a + (i+1)*dx)){
                break;
            }
            i++;
        }
        i++;
        while(i < n){
            if(f(a + i*dx) <= f(a + (i+1)*dx)){
                break;
            }
            i++;
        }
        if(i >= n){
            i = 0;
            dx = dx/2;
            n = n*2;
            continue;
        }
        a = a + (i - 1)*dx;
        b = a + (i + 1)*dx;
        if((minflag == 1)&&(fabs(a-b) <= eps))
            break;
        i = 0;
        n = 4;
        dx = dx/2;
        minflag = 1;
    }
    if (minflag == 0){
        if(err)
            *err = NO_MIN;
        return 0;
    }
    else
        if(err)
            *err = OK;
    return f( ((f(a)*(a + 3*b)) + (f(b)*(b + 3*a)) - (4*f((a+b)/2)*(a + b)))/(2*f(a) + 2*f(b) - 4*f((a+b)/2))/2 );
}
