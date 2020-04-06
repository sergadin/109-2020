#include <iostream>
#include "math.h"
#include "approx.h"
#define E 2.718281828

using namespace std;

int main()
{
	double *x;
	double *y;
	double *y1;
	int n;
	double x0;
	double trueans;
	double res;

	//Первый тест (синус)
	n = 3;
	x = (double *)malloc(n * sizeof(double));
	y = (double *)malloc(n * sizeof(double));
	y1 = (double *)malloc(n * sizeof(double));
	x[0] = -1;
	x[1] = 0;
	x[2] = 1;
	y[0] = sin(x[0]);
	y[1] = sin(x[1]);
	y[2] = sin(x[2]);
	y1[0] = cos(x[0]);
	y1[1] = cos(x[1]);
	y1[2] = cos(x[2]);
	Approx A(n, x, y, y1);
	x0 = 0.523599;
	trueans = 0.5;
	res = A.Hermite(x0);
	cout << "sin(" << x0 << ")=" << res << ". Correct answer is " << trueans  << endl;
	free(x);
	free(y);
	free(y1);

	//Второй тест (квадрат)
	n = 2;
	x = (double *)malloc(n * sizeof(double));
	y = (double *)malloc(n * sizeof(double));
	y1 = (double *)malloc(n * sizeof(double));
	x[0] = 1;
	x[1] = 2;
	y[0] = x[0] * x[0];
	y[1] = x[1] * x[1];
	y1[0] = 2 * x[0];
	y1[1] = 2 * x[1];
	Approx B(n, x, y, y1);
	x0 = 0.2;
	trueans = x0 * x0;
	res = B.Hermite(x0);
	cout << "sqr(" << x0 << ")=" << res << ". Correct answer is " << trueans  << endl;
	free(x);
	free(y);
	free(y1);

	//Третий тест (экспонента)
	n = 4;
	x = (double *)malloc(n * sizeof(double));
	y = (double *)malloc(n * sizeof(double));
	y1 = (double *)malloc(n * sizeof(double));
	x[0] = -1;
	x[1] = 0;
	x[2] = 1;
	x[3] = 3;
	y[0] = y1[0] = pow(E,x[0]);
	y[1] = y1[1] = pow(E,x[1]);
	y[2] = y1[2] = pow(E,x[2]);
	y[3] = y1[3] = pow(E,x[3]);
	Approx C(n, x, y, y1);
	x0 = 2;
	trueans = 7.389056;
	res = C.Hermite(x0);
	cout << "exp(" << x0 << ")=" << res << ". Correct answer is " << trueans  << endl;
	free(x);
	free(y);
	free(y1);


	return 0;
}
