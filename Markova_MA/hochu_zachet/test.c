
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define T 1000
#define eps 1e-5
 /**
    ** Позиция (индекс) минимального элемента, значение которого больше 
	**среднего арифметического элементов строки, минимальна (в других строках такой элемент стоит правее)
    **
    ** Параметры:
    **   а: одномерная матрица рациональны чисел.
    **   n: количество строк .
    **   k: количесвто столбцов.
    ** Идем по строкам и ищем подходящий условиям элемент.
    **
    **
    ** Возвращаемое значение:
    **   Функция возвращает номер строки.
    **
    **   Элементы массива a не изменяют свой порядок.
    **
    */

double alpha;
double i (double (*f)(double), double a, double b, int n);
double i (double (*f)(double), double a, double b, int n)
{
	double I2 = 0, h = (b - a)/n, h1;
	h1 = a + h;
	for(int i = 1; i < n; i++)
		{
			I2 += (*f)(h1);
			h1 += h;
		}
	return (2*I2 + (*f)(a) + (*f)(b))*h/2;
}
double integral(double (*f)(double), double a, double b);
double integral(double (*f)(double), double a, double b)
{
	double I1 = 0, I2 = 0, state;
	int check = 0, n = 128;
	if(a >= b)
	{
		//*perr = INT_ND;
		return I2;
	}
	I1 = i(f, a, b, n);
	I2 = i(f, a, b, 2*n);
	n *= 2;
	while(fabs(I1 - I2) > eps && check < T)
	{
		check++;
		n *= 2;
		I1 = I2;
		I2 = I2 = i(f, a, b, n);
		//printf("%e\n", I2);
	}
	if(check >= T)
	{
		return I1;
	}
	return I2;
}
double root(double (*f)(double), double a, double b);	
double root(double (*f)(double), double a, double b)
{
	double m = (a + b)/2;
	if((*f)(a) * (*f)(b) > 0)
	{
		return m; 
	}
	if((*f)(a) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	while(fabs(b - a) < eps)
	{
		if((*f)(m) < 0)
		{
			a = (*f)(m);
		}
		else
		{
			b = (*f)(m);
		}
		m = (a + b)/2;
	}
	return m;
}
double f (double x);
double f (double x)
{
	return sqrt(x + 1/(x*x + 1));
}
double f1 (double x);
double f1 (double x)
{
	return integral(f, 1, x) - alpha*x;
}
int main() {
	int a = 2, b = 10;
	double res = 0;
	if (scanf("%lf", &alpha) != 1) {
		//err = ERROR_READ;
		return -1;
	}
	//printf("kyky\n");
	res = root(f1, a, b);
		printf("%lf\n", res);
	//fclose(outp);
	return 0;
}