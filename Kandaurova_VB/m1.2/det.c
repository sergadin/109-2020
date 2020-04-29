#include <stdio.h>
#include "det.h"
#include <math.h>
#include <stdlib.h>

void swap(double *data, int n, int row1, int row2) {
	double t;
	for(int i = 0; i < n; i++) {
		t = EL(data, n, row1, i);
		EL(data, n, row1, i) = EL(data, n, row2, i);
		EL(data, n, row2, i) = t;
	}
}
void plus(double *data, int n, int row1, int row2, double s) {
	for(int i = 0; i < n; i++)
		EL(data, n, row1, i) += s * EL(data, n, row2, i);
}

double dete(double *data, int n) {
    double det = 1, s;
    int maxi, sign = 1;
    for(int j = 0; j < n; j++) {
		maxi = j;
		for (int i = j + 1; i < n; i++) {
			if (fabs(EL(data, n, i, j)) > fabs(EL(data, n, maxi, j))) 
				maxi = i;
		}
		if (maxi != j) {
            swap(data, n, maxi, j);
			sign *= -1;
		}
		for (int k = j + 1; k < n; k++) {
			s = EL(data, n, k, j)/EL(data, n, j, j);
            plus(data, n, k, j, (-1) * s);
		}
		det *= EL(data, n, j, j);
	}
      return sign * det;  
}
