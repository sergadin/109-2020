//2. Вычислить интеграл от данной функции f(x) на данном отрезке [a,b] по составной формуле 2.2. трапеций с N отрезками;

#include<stdio.h>
#include<math.h>

#include"2.h"
double square(double x0, double x1, RRFunc f){
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
	return -1;
}

double solve2(double a0, double b0, int N, RRFunc f){
	double res = 0;
	double h = (b0 - a0)/N; //кусочки на которые делим
	for(double i = a0 ; i < b0 ; i += h) {
		res += square(i, i + h, f); 
// считаем площадь на кусочках и складываем

//		printf("i- = %lf  i = %lf res = %lf\n",i,  i + (b0 - a0)/N, res);
//		printf("f(i-) = %lf  f(i) = %lf\n",(*f)(i), (*f)(i + (b0 - a0)/N)) ;
	
	}   	
	return res;
}
