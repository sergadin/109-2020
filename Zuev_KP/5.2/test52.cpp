#include <iostream>
#include "kuslin.h"

using namespace std;

int main()
{
	int n0 = 5;
	double *x = (double*) malloc(n0 *sizeof(double));
	double *y = (double*) malloc(n0 *sizeof(double));
	double x0 = 9;
	double y0[] = {0};
	for(int i = 0; i < n0; i++)
	{
		x[i] = i;
		y[i] = i;
	}
	klin l(n0, x, y);
	y0[0] = l.newPoint(x0);
	for(int i = 0; i < 1; i++)
	{
		cout<< "" << y0[i] <<endl;
	}
	return 0;
}
