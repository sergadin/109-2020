
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 /**
    ** Позиция (индекс) минимального элемента, значение которого больше 
	**среднего арифметического элементов строки, минимальна (в других строках такой элемент стоит правее)
    **
    ** Параметры:
    **   а: одномерная матрица рациональны чисел.
    **   n: количество строк .
    **   k: количесвто столбцов.
    ** Идем по строкам и ищем подходящий условиям элемент.
    **
    **
    ** Возвращаемое значение:
    **   Функция возвращает номер строки.
    **
    **   Элементы массива a не изменяют свой порядок.
    **
    */
void f (double *a, int n, int m);
void f (double *a, int n, int m)
{
	int i , j, sum = 0, max = 0, pos_j = 0, pos_i = 0;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			sum += a[i*m + j];
		}
		sum /= m;
		max = sum;
		for(j = 0; j < m; j++)
		{
			if(a[i*m + j] > max)
			{
				if(pos_j == -1 || pos_j < j)
				{	
					pos_j = j;
					pos_i = i;
				}
			}
		}
	}
	//printf("%d", pos_i);
	//return pos_i;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(i != pos_i && a[i*m + j] < a[pos_i*m + j])
			{
				a[i*m + j] = a[pos_i*m + j];
			}
		}
	}
}

int main() {
	int n, m, i, j;
	double *a;
	FILE *inp, *outp;
	if (!(inp = fopen("input.txt","r")) )
	{
		printf("ERROR\n");
		return -1;
	}
	if ((outp = fopen("output.txt", "w")) == NULL) 
	{
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }
	if (fscanf(inp, "%d", &n) != 1 || fscanf(inp, "%d", &m) != 1) {
		fclose(inp);
		//err = ERROR_READ;
		return -1;
		//break;
	}
	if (!(a = (double *)malloc(sizeof(double) * n * m) )) {
		printf("Not enough memory\n");
		fclose(inp);
		fclose(outp);
		return -1;
	}
	else
	{
		for (i = 0; i < m * n; ++i)
		{
			if (fscanf(inp, "%lf", &a[i]) != 1) {
				fclose(inp);
				//err = ERROR_READ;
				fclose(inp);
				fclose(outp);
				free(a);
				return -1;
			}
		}
		fclose(inp);
	}
	/*if (err != SUCCESS) {
		ERROR_RE(err);
		free(a);
		return -1; 
	}*/
	//printf("kyky\n");
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			printf("%lf", a[i*m + j]);
		}
		//fprintf(outp, "\n");	
		printf("\n");
	}
	free(a);
	//fclose(outp);
	return 0;
}