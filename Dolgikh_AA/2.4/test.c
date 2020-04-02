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
	double A[18],B[18],trueans[18];
	int N[18];
	RRFUN F[18];
	int i;
	FILE *input;

	//Записываем массив тестовых функций
	F[0] = F[1] = F[2] = sin;
	F[3] = F[4] = cos;
	F[5] = F[6] = tan;
	for(i = 7; i <= 11; i++)
		F[i] = square;
	F[12] = F[13] = F[14] = cube;
	F[15] = F[16] = F[17] = exp;

	//Записываем массивы концов отрезков, числа отрезков и правильных ответов
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		return -1;
	}
	for(i = 0; i < 18; i++)
	{
		if(fscanf(input,"%lf %lf %d %lf", &A[i], &B[i], &N[i], &trueans[i]) != 4)
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
	for(i = 0; i < 18; i ++)
	{
		res = gaussintegration(F[i], A[i], B[i], N[i]);
		fprintf(stdout, "Test #%d ", i + 1);
		if(fabs(res - trueans[i]) > eps)
		{
			fprintf(stdout, "Wrong answer. Correct answer: %lf your answer: %lf\n", trueans[i], res);
		}
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
