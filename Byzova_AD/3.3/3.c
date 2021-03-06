//3. Вычислить минимальное значение данной функции f(x) с заданной точностью ε методом построения параболы с поиском трех точек с помощью  измельчением равномерной сетки.
#include<stdio.h>
#include<math.h>

#include"3.h"

//#define K (3 - sqrt(5)) / 2


double minimum(RRFunc f, double eps, double a, double b, ErrorCode *error)
{
	int i;
	double a_0;
	double eps_double = 1e-7;
	int n = 10; // количество частей на которые делим отрезок
	int count_it = 0; // количество итераций
   	double min_x; // a + h * count... будет точкой минимума
    int max_it = 10; // максимально разрешенное количество итераций
	//длина частей отрезка, значение минимума функции, вспомогательная точка для середины отрезка [a,b], коэффициенты параболы
	double h = (b - a)/n, min, c, A, B;
   	double	x_min; // результат работы функции - точка минимума
	*error = INT_OK;
	//пока длина отрезка меньше eps и количесвто итераций допустимо
	while (fabs(b - a) >= eps && (count_it <= max_it)) {
		//изначально минимум полагаем в нач згачении
		min = (*f)(a);
		min_x = a;
		// перебираем значения мало отличающихся аргументов
		// и запоминаем на каком значении i у нас минимум
		for (a_0 = a + h, i = 1; i <= n; a_0 += h, i++) {
			if (min >= (*f)(a_0)) { 
				min = (*f)(a_0);
				min_x = a_0; 
			}
//		printf("i = %lf (*f)(i) = %lf	min_x = %lf\n", a_0,(*f)(a_0), min_x);	
		}
		// если минимум остался в начальной точке, то приближаем b
		if (fabs(fmin(fmin(min_x, a), 1)) <= eps_double) {
			b = a + h * 2;
//			printf("если min_x = a (min_x = %lf) и b = %lf\n", a, b);
		}
		else {
			//если в точке b минимум, то пододвигаем a ближе к b
			if (fabs(fmin(fmin(min_x, b), 1)) <= eps_double) {
				a = b - h * 2;		// a = a + h * (count_h_min - 2);
//			printf("если min_x = b (min_x = %lf) и a = %lf\n", b, a);
			}
			else {
				// сближаем концы отрезка
				b = min_x + h;
				a = b - 2*h;
//		printf("min_x = %lf", min_x);	
//			printf("a = %lf\n", a);
//			printf("b = %lf\n", b);
			}
//		printf("min_x = %lf", min_x);	
		}
		//увеличиваем n
		//и уменьшаем h 
		n *= 10;
		h /= 10;
		count_it++;
	}
	if ((count_it >= max_it) && fabs(b - a) >= eps)
	{
		*error = INT_ERROR;
		return -1;
	}
	// ищем коэфф параболы проходящей через концы и середину данного отрезка
	// Ax^2 + Bx + C = f(x)
	// (x1,y1) (a, (*f)(a))
	// (x2,y2) (b, (*f)(b))
	// (x3,y3) ((a+b)/2, (*f)((a+b)/2))
	// минимум параболы
	c = (a + b) / 2; // середина отрезка
	A = ( (*f)(c) - (c * (((*f)(b)) - (*f)(a)) + b * (*f)(a) - a * (*f)(b))/( b - a ) ) / (c * (c - a - b) + a * b); 
	B = ( (*f)(b) - (*f)(a) )/(b - a) - A*(a + b);
//	printf("A = %lf\n", A);
	x_min = (-1 * B) / (2 * A); // минимум параболы
//	printf("x_min = %lf (*f) = %lf	в границах [%lf,%lf]", x_min, (*f)(x_min), a, b);	
	// если не в границах отрезка выбираем из того что есть
	if((x_min < a) || (x_min > b)) {
//			printf("\nвышли за границу\n");
			return 	fmin((*f)(c), fmin((*f)(a), (*f)(b)));
	}
	return (*f)(x_min);
}


/*

double sign(double a){
	if (a == 0 ) return 0;
	if (a < 0) return -1;
	else return 1;
}

double ch(double a, double b, double c){
	double epsil  = 0.00001;
	if( fabs(a - b) < epsil*fmin(1, fmin(a, b))  && 
		fabs(a - c) < epsil*fmin(1, fmin(a, c))  && 
		fabs(c - b) < epsil*fmin(1, fmin(c, b)) )  {
		return 1;
	} 
	else { 
		return 0;
	}
}

double minim(double a , double c, double eps, RRFunc f) {
	double x = (a + c) / 2;
	double w = (a + c) / 2;
	double v = (a + c) / 2;
	double fx = (*f)(x);
	double fw = (*f)(x);
	double fv = (*f)(x);
	double fu = (*f)(x);
	double g;
	double u;
	double d = c - a;
    double e = c - a;	
//	while ( (c - a) < eps ) { // wrong
	for (int i = 0; i < 100000; i++) {
	g = e;
	e = d;	
	if( ch(x, w, v)*ch(fx, fw, fv) == 0 ) {
		//find u points x1 = a x2 = x x3 = c
		u = x - ( (x - a)*(x - a)*(fx - (*f)(c)) - (x - c)*(x - c)*(fx - (*f)(a)) ) / (2 * ( (x - a)*(fx - (*f)(c)) - (x - c)*(fx - (*f)(a)) ));
		if( u < (a + eps) && u > (c - eps) && fabs(u - x) < g/2 ) {
			// take u
			d = fabs(u - x);
		}	
	}
	else {
		if ( x < (c - a)/2 ) {
			u = x + K*(c - x); // золотое сечение [x;c]
			d = c - x;
		}
		else{
			u = x + K*(x - a); //золотое сечение [a;x]
			d = x - a;
		}
	}
	if (fabs(u - x) < eps) {
		u = x + sign(u - x) * eps; // func sign
		fu = (*f)(u);
	}
	if (fu <= fx){
		if(u >= x) {
			a = x;
		}
		else {
			c = x;
			v = w;
			w = x;
			x = u;
			fv = fw;
			fw = fx;
			fx = fu;
		}
	}
	else {
		if(u >= x) {
			c = u;
		}
		else {
			a = u;
		}
		if(fu <=fw || w == x) {
			v = w;
			w = u;
			fv = fw;
			fw = fu;
		}
		else {
			if(fu <= fv || v == x || v == w) {
				v = u;
				fv = fu;
			} 
		}
	}
	}	
return fx;
}
*/
