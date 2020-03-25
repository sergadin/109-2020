#include<stdio.h>
#include<math.h>
#include"inte.h"
#define max2(a,b) ((b) > (a) ? (b) : (a))
#define max3(a, b, c) (max2(max2((a), (b)), (c)))


double sin(double x);
double line(double x);
double square(double x);
double justzero(double x);
double modul(double x);

int main(void)
{
	int i, num = 4;
	double resi, eps = 0.1;
	double trueans[] = {16.25, 2.5, 6.3, 0};
	RRF funcs[] = {sin, line, square, justzero};
	double a = 2;
	double b = 3;
	int n = 10000;
	for(i = 0; i < num; i++)
	{
		resi = norminteg(a, b, eps, funcs[i]);
		printf("correct:\n%lf\nmy:\n%lf\n", trueans[i], resi);
	}


}


double sin(double x)
{
	return sin(1/x);
}

double line(double x)
{
	return x;
}

double square(double x)
{
	return x*x;
}

double justzero(double x)
{
	return x*0;
}

double modul(double x)
{
	if(x < 0)
		return -x;
	else
		return x;
}
