#include "libs.h"

/**
** Вычисление определенного интеграла на отрезке [a, b] с заданной точностью EPS методом трапеций с n отрезками.
**
** Параметры:
**     FUN f: подынтегральная функция;
**     double a: начало отрезка;
**     double b: конец отрезка;
**     double eps: точность вычислений.
**
** Вычисление интеграла методом трапеций подразумевает деление отрезка на n частей 
** до тех пор, пока не будет соблюдаться правило Рунге.
** 
** Возвращаемое значение: 
**      функция возвращает значение интеграла.
**
*/

double integral(FUN f, double a, double b, double eps){
	double In1 = 0, In2 = 0;
	double x, dx;
	int n = 2;
	dx = (b - a) / n;
	for (int i = 0; i < n; i++) {
		x = a + i * dx;
		In2 += (f(x) + f(x + dx))/2 * dx;
	}
	n *= 2;
	do {
		In1 = In2;
		In2 = 0;
		dx = (b - a) / n;
		for (int i = 0; i < n; i++) {
			x = a + i * dx;
			In2 += (f(x) + f(x + dx))/2 * dx;
		}
		n *= 2;
	} while ((fabs(In1-In2))/3 >= (eps*max_3_dbl(In1, In2, 1)));
	return In2;
}

/**
** Вычисление кореня уравнения f(x)=0 на данном отрезке с заданной точностью EPS методом деления пополам.
**
** Параметры:
**     FUN f: функция, корень которой нужно найти;
**     double a: начало отрезка;
**     double b: конец отрезка;
**     double eps: точность вычислений.
**
** Отрезок делится пополам до тех пор, пока его длина не станет равной нулю с точностью до EPS.  
** 
** Возвращаемое значение: 
**      в случае успеха функция возвращает корень уравнения;
**      иначе - сообщение об ошибке и -1.
**
*/

double root (FUN f, double a, double b, double eps){
	double t, f1, f2;
	double equation;
	if (f(a)*f(b) > 0) {
        printf("ERROR: root cannot be found");
		equation = -1;
		return equation;
	}
    do { 
		f1 = f(a);
		t = (a + b)/2;
		f2 = f(t);
		if (f1 * f2 <= 0) {
			b = t;
		} else {
			a = t;
		}
	} while (!compare(a,b,eps));
    equation = (a + b)/2;
    f1 = f(equation);
	return equation;
}

/**
** Наибольшее из двух чисел типа double.
*/

double max_2_dbl (double x, double y){
	if (x < y) {
		return y;
	} else {
		return x;
	}
}

/**
** Наибольшее из трех чисел типа double.
*/

double max_3_dbl (double x, double y, double z) {
	return max_2_dbl(max_2_dbl(x,y), z); 
}

/**
** Сравнение двух чисел типа double с заданной точностью EPS. 
** В случае равенства возвращается 1, иначе 0.
*/

int compare(double x, double y, double eps) {
	if (fabs(x-y) < (eps* max_3_dbl(x, y, 1))) {
		return 1;
	} else {
		return 0;
	}
}
