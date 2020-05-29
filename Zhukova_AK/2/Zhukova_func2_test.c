#include <stdio.h>
#include "Zhukova_func2.h"

double func1 ( double x); //Функции
double func2 ( double x);
double func3 ( double x);
double func4 ( double x);
double func5 ( double x);

int funcAB (double a, double b, double eps); //Сравнивает два числа

int main (void)
{

	double x = 5; //переменная
	double a; //вспомогательная переменная
	double eps = 0.01; //точность сравнения
	double trueansw[] = {36, 1.4, 4}; //ответы
//36=(5+1)^2
//1.4=2*(1\5)+1
//16=((5^2+1)*2 - 50)^2

	int i, res;
	int n1 = 2;
	int n2 = 3;
	int n3 = 4;

	double (*funcs1[n1])(double); //функции для 1 теста
	funcs1 [0] = func1;
	funcs1 [1] = func2;

	double (*funcs2[n2])(double); //для 2
	funcs2 [0] = func2;
	funcs2 [1] = func4;
	funcs2 [2] = func3;


	double (*funcs3[n3])(double); //для 3
	funcs3 [0] = func5;
	funcs3 [1] = func4;
	funcs3 [2] = func2;
	funcs3 [3] = func1;

	for (i=0; i<3; i++)
	{
		if (i == 0) //1 тест
		{
			a = func (funcs1, n1, x);
		}
		if (i == 1) //2 тест
		{
			a = func (funcs2, n2, x);
		}
		if (i == 2) //3 тест
		{
			a = func (funcs3, n3, x);
		}
		res = funcAB(a, trueansw[i], eps);
		//сравнение правильного и получившегося ответов

		if (res == 0)
		{
			printf ("res%d = OK\n", i+1); //верный ответ
		}
		else
		{
			printf ("res%d = -1\n", i+1); //неверный

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
	x = x + 1;
	return x;
}
double func3 (double x)
{
	x = 1 / x;
	return x;
}
double func4 (double x)
{
	return 2*x;
}

double func5 (double x)
{
	x = (x - 50) * (x - 50);
	return x;
}

int funcAB (double a, double b, double eps)
{
        int help1; //вспомогательные переменные
        double help2;

        help2 =a - b;
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


