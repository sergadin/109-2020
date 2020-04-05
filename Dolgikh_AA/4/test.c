#include "task.h"
#include <math.h>
#include <stdio.h>
#define eps 0.000001

int main()
{
	double X[7], trueans[7];
	FILE *input;
	int i;
	double res;

	//Открываем файл
	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		return -1;
	}
	
	//Читаем данные для тестов
	for(i = 0; i < 7; i++)
	{
		if(fscanf(input,"%lf %lf", &X[i], &trueans[i]) != 2)
		{
			fprintf(stderr, "File reading error\n");
			fclose(input);
			return -1;
		}
	}
	fclose(input);

	//Проводим тесты
	for(i = 0; i < 7; i++)
	{
		fprintf(stdout, "Test #%d ", i+1);
		res = cosine(X[i], eps);
		if(fabs(res - trueans[i]) > eps)
			fprintf(stdout, "Wrong answer\n");
		else
			fprintf(stdout, "OK\n");
	}
	
	return 0;
}
