//Написать программу, которая по значениям x1 ...xn и y1 ...yn вычисляет в данной точке x приближенное значение функции с помощью
//5.2. кусочно-линейной интерполяции;
#include <iostream>
#include <cmath>

#include "5.h"

using namespace std;

int main()
{	
		int n = 10; 
		double x[10] = {-3.545, -2.171, -1.587, -1.253, 0, 1.856, 2.515, 3.316, 3.922, 4};
		double x0 = -0.346;
		double y0[2] = {0, 0};
		double r_answers[2] = {0.989, -1.556};
		double *y1 = (double*) malloc(n *sizeof(double));
		double *y2 = (double*) malloc(n *sizeof(double));
		if ((y1 == NULL) || (y2 == NULL)) {
			cout << "error" << endl;
			return -1;
		}

		for(int i = 0; i < n; i++) {
			y1[i] = sin(x[i] + 2) * cos(x[i] * x[i]) ;
			y2[i] = 0.255 * x[i] * x[i] + 0.25 * x[i] - 1.5;
		}

		interpolution f_1(n, x, y1);
		y0[0] = f_1.inter(x0);

		interpolution f_2(n, x, y2);
		y0[1] = f_2.inter(x0);
		for(int i = 0; i < 2; i++) {	
			cout<<" Правильный ответ = " << r_answers[i] << endl;
			cout<<" Мой ответ = " << y0[i] << endl;
		}
		free(y1);
		free(y2);

return 0;
}

