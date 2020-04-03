//2. Вычислить интеграл от данной функции f(x) на данном отрезке [a,b] по составной формуле 2.2. трапеций с N отрезками;

#include<stdio.h>
#include<math.h>

#include"2.h"
double square(double x0, double x1,RRFunc f){
	double h = fabs(x1 - x0); //длина отрезка
	if ( (*f)(x0)*(*f)(x1) >= 0 && (*f)(x0) >= 0) { //трапеция/треуг./ноль
	return  ( ((*f)(x0) + (*f)(x1)) * h ) / 2;
	}
	if ( (*f)(x0)*(*f)(x1) >= 0 && (*f)(x0) < 0) { //трап./треуг.
	return  - ( fabs((*f)(x0) + (*f)(x1)) * h ) / 2;
	}
	if ( (*f)(x0)*(*f)(x1) < 0 && (*f)(x0) > 0) { //два подобных треуг.
	return ((*f)(x0) - (*f)(x1)) * h / 2 ; 
	//формула получена подсчетами на листочке
	}
	if ( (*f)(x0)*(*f)(x1) < 0 && (*f)(x0) < 0) { //два подобных треуг.
	return - fabs((*f)(x0) - (*f)(x1)) * h / 2 ;
	}
	printf("error");
	return -1;
}

double solve2(double a0, double b0,double eps, int N, RRFunc f){
	double prev_res = 0;
	double next_res = 0;
//	double delta = 0;
	double h = (b0 - a0)/N; //кусочки на которые делим
	for(double i = a0 ; i < b0 ; i += h) {
		prev_res += square(i, i + h, f); 
// считаем площадь на кусочках и складываем

	}

	h /= 2;
	for(double i = a0 ; i < b0 ; i += h) {
		next_res += square(i, i + h, f); 
	}	
	
	while( fabs(next_res - prev_res)/3 >= eps){
	h /= 2;
		prev_res = next_res;
		next_res = 0;
		for(double i = a0 ; i < b0 ; i += h) {
			next_res += square(i, i + h, f); 
		}
	}	
	
return next_res;
}



