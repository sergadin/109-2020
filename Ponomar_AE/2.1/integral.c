#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "integral.h"

double integral(RRF func, double X_a, double X_b, double E)
{
	double curr1 = 0, curr2 = 0, x, dx;
	int n = 2;
	dx = (X_b-X_a)/n;
	for (int i = 0; i < n; i++) {
		x = X_a + i*dx;
		curr2 += func(x + dx) * dx;
	}
	n = n*2;
	while((fabs(curr1-curr2))/3 >= E)
        {
		curr1 = curr2;
		curr2 = 0;
		dx = (X_b-X_a)/n;
		for (int i = 0; i < n; i++) {
			x = X_a + i*dx;
			curr2 += func(x+dx)*dx;
		}
		n = n*2;
	}
	return curr2;
}

