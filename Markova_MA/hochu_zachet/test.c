
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define T 1000
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
typedef enum { INT_OK = 0, INT_NOT, INT_ND } ErrorCode;
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
double integral(double (*f)(double), double a, double b, double eps, ErrorCode *perr);
double integral(double (*f)(double), double a, double b, double eps, ErrorCode *perr)
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
		*perr = INT_NOT;
		return I1;
	}
	*perr = INT_OK;
	return I2;
}
double root(double (*f)(double, ErrorCode), double a, double b, double eps);	
double root(double (*f)(double, ErrorCode), double a, double b, double eps)
{
	double m = (a + b)/2;
	if(perr != NULL)
	{
        *perr = ROOT_OK;
		if((*f)(a, perr) * (*f)(b, perr) > 0)
		{
			*perr = ROOT_NOT;
			return m; 
		}
	}
	if((*f)(a, perr) > 0)
	{
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	while(fabs(b - a) < eps)
	{
		if((*f)(m, perr) < 0)
		{
			a = (*f)(m, perr);
		}
		else
		{
			b = (*f)(m, perr);
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
double f1 (double x, perr);
double f1 (double x, perr)
{
	return integral(f, 1, x) - alpha*x;
}
int main() {
	int a = 2, b = 10;
	double res = 0;
	ErrorCode perr;
	//FILE *inp;
	/*if (!(inp = fopen("input.txt","r")) )
	{
		printf("ERROR\n");
		return -1;
	}*/
	/*if ((outp = fopen("output.txt", "w")) == NULL) 
	{
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }*/
	if (scanf("%d", &alpha) != 1) {
		fclose(inp);
		//err = ERROR_READ;
		return -1;
		//break;
	}
	/*if (err != SUCCESS) {
		ERROR_RE(err);
		free(a);
		return -1; 
	}*/
	//printf("kyky\n");
	res = root(f1, a, b, m, eps, perr);
	if (perr == INT_OK)
		printf("%lf\n", res);
	//fclose(outp);
	return 0;
}