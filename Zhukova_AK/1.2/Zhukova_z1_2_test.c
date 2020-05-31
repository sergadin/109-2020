#include <stdio.h>
#include <math.h>
#include "Zhukova_z1_2.h"

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
	double root;
	int n = 4; //количество тестов
	double eps[] = {0.001, 0.1, 0.01, 0.01}; //точность сравнения
	double a[] = {-1, -2.5, -8, 4}; //левые концы отрезков
	double b[] = {5, 0, 15, 19}; //правые концы отрезков
	double trueansw[] = {2, -2, 0, 5}; //правильные ответы
//например, [a[0] , b[0]] - отрезок для первой функции func1, точность сравнения - eps[0]

	double (*funcs[n])(double); //функции для тестов
        funcs [0] = func1;
        funcs [1] = func2;
        funcs [2] = func3;
        funcs [3] = func4;


	for (i=0; i<n; i++)
	{
		root = findroot (funcs[i], a[i], b[i], eps[i]);
		//поиск корня

//		printf ("x=%f   trueansw=%f\n", root, trueansw[i]);

		if (funcAB(trueansw[i], root, eps[i]) == 0)
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
        x = x*x*x - 8;
        return x;
}
double func2 (double x)
{
        x = x*x + 5*x + 6;
        return x;
}
double func3 (double x)
{
        x = exp(x) - 1;
//	x = x - 1/x;
        return x;
}
double func4 (double x)
{
	x = x*x*x*x - 25*x*x;
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
