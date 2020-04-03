#include<stdio.h>
#include<math.h>

#include"func.h"

double solve1(double a0, double b0, double eps, RRFunc f) {
	double a = a0, b = b0;
    double mid = (a0 + b0)/2;
	double fa , fb, fmid = 0; 
	double len = b - a;

	if( (*f)(a)*(*f)(b) > 0 ) { // считаем, что в таком случае корня нет
		return -1;
	}
	
	if((*f)(a) == 0) {
	return a;
	}
	
	if((*f)(b) == 0) {
	return b;
	}


	while(len > eps) { // пока окрестность корня недостаточной точности
		
		mid = (a + b)/2; // середина отрезка
		fmid = (*f)(mid); // значение функции на середине отрезка
		
		if( (*f)(a)*fmid <= 0 ) { // если эти значения разных знаков
			b = mid;             // то корень лежит между данными аргументами 
			fb = fmid;          // сдвигаем границу b в середину отрезка 
		}
		else {
			a = mid;     // если нет, то корень может быть в другой половине
			fa = fmid;  // сдвигаем границу a в середину отрезка
		}

		len = b - a; // получившаяся длина отрезка
	}
	
	return (a + b)/2; // 'корень' с учетом погрешности
	len = fa + fb; // чтобы не ломалась за неиспользование fa и fb
}




