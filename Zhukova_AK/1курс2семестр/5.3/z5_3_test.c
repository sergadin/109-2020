#include <stdio.h>
#include <math.h>
#include "z5_3.h"

double func2 ( double x); //Функции
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

        double eps = 0.5; //точность сравнения
        double a1[] = {0, 1, 2, 3, 4, 5 }; //x1, ..., xn
        double b1[] = {sin(0), sin(1), sin(2), sin(3), sin(4), sin(5)}; //y1, ..., yn

        double a2[] = {1, 2, 3, 4 }; //x1, ..., xn
        double b2[] = {func2(1), func2(2), func2(3), func2(4)}; //y1, ..., yn

        double a3[] = {1, 2, 3, 4 }; //x1, ..., xn
        double b3[] = {func3(1), func3(2), func3(3), func3(4) }; //y1, ..., yn

        double a4[] = {1, 2, 3, 4 }; //x1, ..., xn
        double b4[] = {func4(1), func4(2), func4(3), func4(4) }; //y1, ..., yn

	double x[] = {0.5, 2.5, 3.5, 1.5};
        double trueansw[] = {sin(0.5), func2(2.5), func3(3.5), func4(1.5)}; //правильные ответы
//например, [a[0] , b[0]] - отрезок для первой функции func1, точность сравнения - eps


        for (i=0; i<tests; i++)
        {
		if (i == 0)
		{
			x[i] = func (a1, b1, x[i], eps, 6);
		}
		if (i == 1)
		{
			x[i] = func (a2, b2, x[i], eps, 4);
		}
		if (i == 2)
		{
			x[i] = func (a3, b3, x[i], eps, 4);
		}
		if (i == 3)
		{
			x[i] = func (a4, b4, x[i], eps, 4);
		}

                printf ("x=%f   trueansw=%f\n", x[i], trueansw[i]);
                //x - полученный результат
                //trueansw - правильный ответ


                if (funcAB(trueansw[i], x[i], eps) == 0)
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

double func2 ( double x)
{
	x = x*x*x + x*x + 1;
	return x;
}
double func3 ( double x)
{
	x = 1/x;
	return x;
}
double func4 ( double x)
{
	x = 5*x + 10;
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






