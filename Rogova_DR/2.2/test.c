#include<stdio.h>
#include<math.h>
#include"inte.h"
#define max2(a,b) ((b) > (a) ? (b) : (a))
#define max3(a, b, c) (max2(max2((a), (b)), (c)))


double cube(double x);
double line(double x);
double square(double x);
double justzero(double x);
double modul(double x);

int main(void)
{
	int i, num = 4;
	double res, e = 0.001;
	double trueans[] = {16.25, 2.5, 6.3, 0};
	RRF funcs[] = {cube, line, square, justzero};
	double a = 2;
	double b = 3;
	int n = 10000;
	for(i = 0; i < num; i++)
	{
		res = integ(a, b, n, funcs[i]);
		if(modul(res - trueans[i]) < e*max3(res, trueans[i], 1))
		{
			printf("correct:\n%lf\nmy:\n%lf\nwin)))\n", trueans[i], res);
		}
		else
		{
			printf("correct:\n%lf\nmy:\n%lf\nlose(((\n", trueans[i], res);
		}
	}


}


double cube(double x)
{
	return x*x*x;
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
