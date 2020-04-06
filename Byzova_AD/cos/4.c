// Написать программу вычисления значения  cos в заданной точке x и с заданной точностью ε суммированием ряда Тейлора. Сравнить с точным ответом
// cos = 1 - x^2 /2 + x^4 / 4 -... + (-1)^n * x^2n / (2n)! + o(x^2n);
#include<stdio.h>
#include<math.h>

#include"4.h"

double Taylor_cos(double x, double eps){
	double result = 1;
	double tay = 1;
	int n = 1;
	while ( fabs(tay) > eps ) {
		tay = (-1) * tay * x * x / (n * (n + 1));
		result += tay;
//		printf("tay : %lf\n result : %lf", tay, result);
		n += 2;
	}
return result;
}

