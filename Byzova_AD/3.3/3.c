//3. Вычислить минимальное значение данной функции f(x) с заданной точностью ε методом построения параболы с поиском трех точек с помощью  измельчением равномерной сетки.
#include<stdio.h>
#include<math.h>

#include"3.h"

#define K (3 - sqrt(5)) / 2

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
	while ( (c - a) < eps ) {
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

