#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
/*
Функция читает строку из файла и возвращает указатель на эту строку
*/
char *readstring(FILE *f) {
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, f);
	if(s) {
		int len = strlen(s);
		char *result = malloc(len + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;
}
/*
Функция ищет минимальную строку матрицы непосредственным перебором и выводит ее номер
*/
int find(char **matrix, int n, int m) {
    int k = 0, n_i = 0, n_k = 0, S, l_i, l_k, x_i, x_k;
    for(int i = 1; i < n; i++) {
        n_i = 1, n_k = 1;
        for(int j = 0; j < m; j++) {
            n_k += strlen(matrix[k * m + j]) - 1;
            n_i += strlen(matrix[i * m + j]) - 1;
        }
        if(n_k < n_i) 
            S = n_k;
        else
            S = n_i;
        l_i = 0;
        l_k = 0;
        x_i = 0;
        x_k = 0;
        for(int j = 0; j < S; j++) {
            if(j + x_i == strlen(matrix[i * m + l_i]) - 1) {
                l_i++;
                x_i += strlen(matrix[i * m + l_i]) - 1;
            }
            if(j + x_k == strlen(matrix[k * m + l_k]) - 1) {
                l_k++;
                x_k += strlen(matrix[k * m + l_k]) - 1;
            }
            if(matrix[i * m + l_i][j - x_i] < matrix[k * m + l_k][j - x_k]) {
                k = i;
                break;
            }
            if(matrix[i * m + l_i][j - x_i] > matrix[k * m + l_k][j - x_k]) {
                break;

            }
        }
    }
    return k;
}
/*
Функция вычеркиванет из слова A_pq букв слова A_kq.
*/

void fun(char **matrix, int n, int m, int k){
int a, b = 0;
for(int i = 0; i < n; i++) {
    if(i != k) {
        for(int j = 0; j < m; j++) {
            b = 0;
            for(int t = 0; t < strlen(matrix[i * m + j]); t++) {
                a = 0;       
                for(int s = 0; s < strlen(matrix[k * m + j]); s++) {
                    if(matrix[i * m + j][t] == matrix[k * m + j][s]) {
                        a = 1;
                        break;
                    }                
                }
                if(a != 0) {
                    b = 1;
                    for(int r = t; r < strlen(matrix[i * m + j]) - 1; r++) {
                        matrix[i * m + j][r] = matrix[i * m + j][r + 1];
                    }
                    matrix[i * m + j][strlen(matrix[i * m + j]) - 1] = '\0';
                    t--;
                }
            }
        }
    }
}
}
/*
Функция печатает матрицу в файл f
*/
void print(char **matrix, int n, int m, FILE *f) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < strlen(matrix[i * m + j]); k++) {
                if(matrix[i * m + j][k] != '\n')
                    fprintf(f, "%c", matrix[i * m + j][k]);
            }
            fprintf(f, "\n");
        }
    }
}
