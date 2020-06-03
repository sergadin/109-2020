//В текстовом файле записана матрица действительных чисел. Формат данных: два натуральных числа n и m, задающих соответственно число строк и столбцов матрицы, и последовательность действительных чисел, соответствующая записи матрицы по строкам. Требуется найти строчку матрицы, удовлетворяющую заданному условию (если таких несколько, то выбираем строку с минимальным номером), выполнить указанное преобразовании матрицы, и напечатать получившуюся матрицу с сохранением формата в
//УСЛОВИЕ ВЫБОРА
//Позиция (индекс) минимального элемента, значение которого больше среднего арифметического элементов строки, минимальна (в других строках такой элемент стоит правее).
//СЛОЖЕНИЕ
//Заменить A_pi на скалярное произведение (A_pi, A_pi+1, A_pm) и (A_ki, A_ki+1, A_km).
#include<stdio.h>
#include<stdlib.h>

#include"52.h"

void print_matrix(FILE *output, int n, int m, double *matrix){
    fprintf(output, "\nтеперь матрица\n");
	for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fprintf(output, "%lf\t", matrix[i * m + j]);
        }
    fprintf(output,"\n");
    }
}

// среднее арифметическое элементов строки
double arif_m(int m, double *matrix, int num_str) {
	double result = 0;
	for(int j = 0; j < m; j++) {
		result += matrix[num_str * m + j];
	}
	result = result / m;
	return result;
} 

//	Заменить A_pi на скалярное произведение (A_pi, A_pi+1, A_pm) и (A_ki, A_ki+1, A_km).
void skal(int n, int m, double *matrix, int str_var, int i, int k_str) {
	
if ( i == m - 2 ) // p m-1  p m
	matrix[str_var * m + i] = matrix[str_var * m + m - 2] * matrix[k_str * m + m - 2] 
							+ matrix[str_var * m + m - 1] * matrix[k_str * m + m - 1];
if ( i == m - 1) 
	matrix[str_var * m + i] = matrix[str_var * m + m - 1] * matrix[k_str * m + m - 1];
if ( i < m - 2) 
	matrix[str_var * m + i] = matrix[str_var * m + i] * matrix[k_str * m + i] 
							+ matrix[str_var * m + i + 1] * matrix[k_str * m + i + 1]
							+ matrix[str_var * m + m - 1] * matrix[k_str * m + m - 1];	
}

void solve(FILE *output, int n, int m, double *matrix) {
double now_min;	
double arifm_m = 0;
int index = -1;
int need_str = 0;
	for(int i = 0; i < n; i++) {
        arifm_m = arif_m(m, matrix, i);
		for(int j = 0; j < m; j++) {	
			if ( matrix[i * m + j] > arifm_m) {
				if(index == -1){ //?
					now_min = matrix[i * m + j];
					index = j;
				}
				if(matrix[i * m + j] < now_min && (j) < index) {
					now_min = matrix[i * m + j];
					index = j;
					need_str = i;
				}
			}
		}
	}
//	Заменить A_pi на скалярное произведение (A_pi, A_pi+1, A_pm) и (A_ki, A_ki+1, A_km). k - найденная строка
	for(int i = 0; i < n; i++) {
		if(i != need_str) {
			for(int j = 0; j < m; j++) {	
				skal(n, m, matrix, i, j, need_str) ;
			}
		}
	}
	print_matrix(output, n, m, matrix);
}



