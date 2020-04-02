#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task.h"
#define eps 0.000001
#define E 2.718281828

double square(double x);
double cube(double x);
double exp(double x);


int main(void)
{
	double res, c;
	double A[15],B[15],trueans[15];
	RRFUN F[15];
	int i;
	FILE *input;
	ErrorCode err;

	//Записываем массив тестовых функций
	F[0] = F[1] = F[2] = sin;
	F[3] = F[4] = cos;
	F[5] = F[6] = tan;
	for(i = 7; i <= 10; i++)
		F[i] = square;
	F[11] = F[12] = F[13] = cube;
	F[14] = exp;

	//Записываем массивы концов отрезков, числа отрезков и правильных ответов
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		return -1;
	}
	for(i = 0; i < 15; i++)
	{
		if(fscanf(input,"%lf %lf %lf", &A[i], &B[i], &trueans[i]) != 3)
		{
			fprintf(stderr,"File reading error\n");
			fclose(input);
			return -1;
		}
		//Где надо, меняем концы отрезков местами
		if(A[i] > B[i])
		{
			c = A[i];
			A[i] = B[i];
			B[i] = c;
		}
	}
	fclose(input);

	//Тесты
	for(i = 0; i < 15; i ++)
	{
		res = integrate(F[i], A[i], B[i], eps, &err);
		fprintf(stdout, "Test #%d ", i + 1);
		if(err == INT_NOTOK)
			fprintf(stdout, "Integration error\n");
		if(fabs(res - trueans[i]) > eps)
			fprintf(stdout, "Error %lf\n", fabs(res - trueans[i]));
		else
			fprintf(stdout, "OK\n");
	}



	return 0;
}

double square(double x)
{
	return x * x;
}
double cube(double x)
{
	return x * x * x;
}
double exp(double x)
{
	return pow(E, x);
}
