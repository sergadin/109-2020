//5. Äëÿ çàäàííîãî äåéñòâèòåëüíîãî ÷èñëà x è ôóíêöèé f è g âû÷èñëèòü ïåðâîå çíà÷åíèå âèäà y = f(f(f ...f(x)...), êîòîðîå óäîâëåòâîðÿåò óñëîâèþ g(y) > 0. для действ нат числа х и функций ф и ж вычислить первое значение вида кот удовл условию

#include<stdio.h>
#include<math.h>

#include"5.h"

double solve5(double x, RRFunc f, RRFunc g){
	double y = (*f)(x);
		
	while ((*g)(y) <= 0) {
		y = (*f)(y);
	}

	return y;
	
}
