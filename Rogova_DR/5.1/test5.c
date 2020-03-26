#include<stdio.h>
#include<math.h>
#include"interpol.h"




double line(double x);
double sqr(double x);
double zer(double x);


int main(void)
{
	double rescor, res;
	double tran[] = {2, 4, 0};
	double x[] = {1, 3, 4, 5, 6, 7};
	double y[] = {0, 0, 0, 0, 0, 0};
	int n = 6;
	double x0 = 2;
	RRF funcs[] = {line, sqr, zer};
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < n; j++)
		{
			y[j] = (*funcs[i])(x[j]);
		}
		rescor = (*funcs[i])(x0);
		res = interpol(x, y, n, x0, funcs[i]);
		printf("correct:\n%lf\nmy:\n%lf\n", rescor, res);
	}

}




double line(double x)
{
	return x;
}

double sqr(double x)
{
	return x*x;
}

double zer(double x)
{
	return x*0;
}
