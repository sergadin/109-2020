#include <stdio.h>
#include <math.h>
#include "z3_3.h"

double func1 ( double x); //Функции
double func2 ( double x);
double func3 ( double x);
double func4 ( double x);

int funcAB (double a, double b, double eps); //Сравнивает два числа a и b с точностью eps
//возвращает 1, если a>b
//-1, если a<b
//0, если a=b


int main (void)
{
        int i;
        int tests = 4; //количество тестов
	int n = 20; //количество отрезков в измельчении

	double minx; //найденый минимум
        double eps = 0.001; //точность сравнения
        double a[] = {-1, -5, 0, -4}; //левые концы отрезков
        double b[] = {5, 0, 3, 19}; //правые концы отрезков
        double trueansw[] = {-16, -1, -1, 0}; //правильные ответы
//например, [a[0] , b[0]] - отрезок для первой функции func1, точность сравнения - eps

        double (*funcs[n])(double); //функции для тестов
        funcs [0] = func1;
        funcs [1] = func2;
        funcs [2] = func3;
        funcs [3] = func4;


        for (i=0; i<tests; i++)
        {
                minx = findmin (funcs[i], a[i], b[i], eps, n);
                //поиск минимума

                printf ("x=%f   trueansw=%f\n", minx, trueansw[i]);
		//x - полученный результат
		//trueansw - правильный ответ


                if (funcAB(trueansw[i], minx, eps) == 0)
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

double func1 (double x)
{
        x = x*x*x - 12*x;
        return x;
}
double func2 (double x)
{
        x = x*x + 6*x + 8;
        return x;
}
double func3 (double x)
{
        x = -cos(x);
        return x;
}
double func4 (double x)
{
        x = x*x*x*x;
        return x;
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







