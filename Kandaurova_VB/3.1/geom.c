#include <stdio.h>
#include "geom.h"

double minim(double a, double b, RRfun fun, double eps){
    int n = 16, i; 
    double h = (b - a)/n, result, left = a, right, now, prev, next;    
    right = left + 2 * h;

    while(h > eps) {
            prev = left;
        	next = prev + h * 2;
            now = left + h;
		for (int i = 1; i < n - 1; i++) {
			if (((*fun)(prev) > (*fun)(now)) && ((*fun)(next) > (*fun)(now))) {
				left += h * (i - 1);
				right = left + 2 * h;

				break;
			}
			prev += h;
			now += h;
			next += h;
		}
		n *= 2;
		h /= 2;
    }
    if(((*fun)(now) != (*fun)(left)) && ((*fun)(now) != (*fun)(right)))
		result = (*fun)(now - ((now - left) * (now - left) * ((*fun)(now) - (*fun)(right)) - (now - right) * (now - right) * ((*fun)(now) - (*fun)(left))) / (2 * ((now - left)*((*fun)(now) - (*fun)(right)) - (now - right) * ((*fun)(now) - (*fun)(left)))));
	else
		result = (*fun)(now);
    return result;
}
