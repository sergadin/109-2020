#include <stdio.h>
#include <math.h>
#include "z4_sin.h"

int funcAB (double a, double b, double eps); //Сравнивает два числа a и b с точностью eps
//возвращает 1, если a>b
//-1, если a<b
//0, если a=b


int main (void)
{
        int i;
        int n = 4; //количество тестов

        double s; //найденый sin
        double eps = 0.001; //точность сравнения
        double a[] = {5, -0.75, 0, 0.4}; //x
        double trueansw[] = {sin(5), sin(-0.75), sin(0), sin(0.4)}; //правильные ответы

        for (i=0; i<n; i++)
        {
                s = sinx (a[i], eps);
                //поиск sin

                printf ("x=%f   trueansw=%f\n", s, trueansw[i]);
                //s - полученный результат
                //trueansw - правильный ответ


                if (funcAB(trueansw[i], s, eps) == 0)
                {
                        printf ("test%d = OK\n", i+1);//верный ответ
                }
                else
                {
                        printf ("test%d = WA\n", i+1);//неверный

                }
        }

        return 0;

}

int funcAB (double a, double b, double eps)
{
        int help1; //вспомогательные переменные
        double help2;

        help2 = a - b;
        help2 = help2 / eps;
        help1 = (int) (help2);

        if (help1 > 0)
        {
                return 1;
        }

        if (help1 < 0)
        {
                return -1;
        }

        if (help1 == 0)
        {
                return 0;
        }
}






