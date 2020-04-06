#include<stdio.h>
#include<math.h>
#include"sum.h"
#define max2(a,b) ((b) > (a) ? (b) : (a))
#define max3(a, b, c) (max2(max2((a), (b)), (c)))

double line(double x);
double sqr(double x);
double zer(double x);


int main(void)
{
	int i, numt = 3;
	double res, epsilon = 0.001;
	double tran[] = {1, 10000, 100000};
	RRF funcs[] = {line, sqr, zer};
	double a = 0;
	double b = 3;
	for(i = 0; i < numt; i++)
	{
		res = findroot(a, b, eps, funcs[i]);
		printf("correct:\n%lf\nmy:\n%lf+-%lf\n", tran[i], res, epsilon);
		
	}
}

double line(double x)
{
	return (x - 1);

}

double sqr(double x)
{
	return x*x;
}

double zer(double x)
{
	return 0*x;
}

