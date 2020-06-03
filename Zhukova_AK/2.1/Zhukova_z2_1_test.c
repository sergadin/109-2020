#include <stdio.h>
#include <math.h>
#include "Zhukova_z2_1.h"

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
        double intf; //интеграл функции
        int n = 4; //количество тестов

	double eps_all = 0.05; //точность сравнения для всех функций

//	int nAB[] = {5000, 5000, 5000, 1000};//количество отрезков
        double a[] = {2, 0, 1, -7}; //левые концы отрезков
        double b[] = {5, 5, 25, 7}; //правые концы отрезков
        double trueansw[] = {39, 12.5, 0.96, 0}; //правильные ответы
//например, [a[0] , b[0]] - отрезок для первой функции func1, точность сравнения - eps_all

        double (*funcs[n])(double); //функции для тестов
        funcs [0] = func1;
        funcs [1] = func2;
        funcs [2] = func3;
        funcs [3] = func4;


        for (i=0; i<n; i++)
        {
                intf = findint (funcs[i], a[i], b[i], eps_all);
                //вычисление интеграла

		printf ("intf=%f   trueansw=%f\n", intf, trueansw[i]);

		//intf - полученный ответ
		//trueansw  - верный ответ

                if (funcAB(trueansw[i], intf, eps_all) == 0)
                {
                        printf ("test%d = OK\n\n", i+1);//верный ответ
                }
                else
                {
                        printf ("test%d = WA\n\n", i+1);//неверный

                }
        }

        return 0;

}

double func1 (double x)
{
	x = x*x;
        return x;
}
double func2 (double x)
{
	x = 5*x - 10;
        return x;
}
double func3 (double x)
{
        x = 1/(x*x);
        return x;
}
double func4 (double x)
{
	x = sin(x);
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
