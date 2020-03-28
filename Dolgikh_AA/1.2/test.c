#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task.h"
#define eps 0.000001

double square2(double x);
double square3(double x);
double square4(double x);
double square37(double x);
double cube2(double x);


int main(void)
{
	double  res, c;
	double A[15],B[15],trueans[15];
	RRFUN F[15];
	int i;
	FILE *input;

	//Записываем массив тестовых функций
	for(i = 0; i < 5; i++)
		F[i] = sin;
	F[5] = F[6] = cos;
	F[7] = square2;
	for(i = 8; i < 12; i++)
		F[i] = square3;
	F[12] = square4;
	F[13] = square37;
	F[14] = cube2;
	
	//Записываем массивы концов отрезков и правильных ответов
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		fclose(input);
		return -1;
	}
	for(i = 0; i < 15; i++)
	{
		if(fscanf(input, "%lf %lf %lf", &A[i], &B[i], &trueans[i]) != 3)
		{
			fprintf(stderr, "File reading error\n");
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
	for(i = 0; i < 15; i++)
	{
		res = newton(F[i], A[i], B[i], eps);
		fprintf(stdout, "Test #%d ", i + 1);
		if(res < A[i] || res > B[i])
			fprintf(stdout, "There is no roots in [a,b] segment. ");
		else
			fprintf(stdout, "Root is %lf ", res);
		if(fabs(res - trueans[i]) > eps)
		{
			fprintf(stdout, "Wrong answer\n");
			return -1;
		}
		else
			fprintf(stdout, "Right answer\n");
	}
	
	return 0;	
}

double square2(double x)
{
	return x * x - 2;
}
double square3(double x)
{
	return x * x - 3;
}
double square4(double x)
{
	return x * x - 4;
}
double square37(double x)
{
	return x * x - 37;
}
double cube2(double x)
{
	return x * x * x - 2;
}
