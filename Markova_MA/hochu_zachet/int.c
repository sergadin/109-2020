#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T 1000
#define eps 1e-16
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
	int n = 128;
	if(a >= b)
	{
		printf("puk");
		//*perr = INT_ND;
		return I2;
	}
	I1 = i(f, a, b, n);
	I2 = i(f, a, b, 4*n);
	n *= 2;
	while(fabs(I1 - I2) > eps )
	{
		//check++;
		n *= 2;
		I1 = I2;
		I2 = i(f, a, b, n);
		//printf("%lf\n", I2);
	}
	/*if(check >= T)
	{
		return I1;
	*/
	printf("I2 %lf\n", I2);
	return I2;
}
double root(double (*f)(double), double a, double b);	
double root(double (*f)(double), double a, double b)
{
	double m = (a + b)/2, int1 = integral(f, 1, a), int2 = integral(f, 1, b);
	if((int1 - alpha*a) * (int2- alpha*b) > 0)
	{
		printf("res1 %lf\n", int1 - alpha*a);
		printf("res2 %lf\n", int2 - alpha*b);
		
		return m; 
	}
	printf("res1 %lf\n", int1 - alpha*a);
	printf("res2 %lf\n", int2 - alpha*b);
	
	while(fabs(b - a) < eps)
	{
		double res = integral(f, 1, m) - alpha*m;
		printf("res = %lf\n", res);
		printf("b - a = %lf", b - a);
		if(integral(f, 1, m) - alpha*m < 0)
		{
			if(integral(f, 1, a) - alpha*a < 0)
				a = m;
			else
				b = m;
		}
		else
		{
			if(integral(f, 1, a) - alpha*a > 0)
				a = m;
			else
				b = m;
		}
		//printf("%lf", (*f)(m));
		printf("b - a = %lf", b - a);
		m = (a + b)/2;
	}
	return m;
}

double f (double x);
double f (double x)
{
	return sqrt(x + 1/(x*x + 1));
}

int main() {
	double a = 2, b = 12;
	double res = 0;
	if (scanf("%lf", &alpha) != 1) {
		//err = ERROR_READ;
		return -1;
	}
	//printf("kyky\n");
	res = root(f, a, b);
		printf("res = %lf\n", res);
	//fclose(outp);
	return 0;
}