#include<stdio.h>
#include<math.h>
#include"inte.h"
#define max2(a,b) ((b) > (a) ? (b) : (a))
#define max3(a, b, c) (max2(max2((a), (b)), (c)))


double si(double x);
double line(double x);
double square(double x);
double justzero(double x);
double modul(double x);

int main(void)
{
	ErrorCode ec;
	int i;
	double resi, eps = 0.1;
	double trueans[] = {0.5, 0.333333, 0, 0.504066};
	RRF funcs[] = {line, square, justzero, si};
	double a = 0.001;
	double b = 1;
	int n = 10000;
	for(i = 0; i < 4; i++)
	{
		resi = norminteg(a, b, eps, funcs[i], &ec);
		if(ec == I_OK)
			printf("correct:\n%lf\nmy:\n%lf\n", trueans[i], resi);
		else
			printf("Ups...");
	}


}


double si(double x)
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
