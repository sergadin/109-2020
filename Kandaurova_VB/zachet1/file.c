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
            //printf("%d %d\n", strlen(matrix[k * m + j]), strlen(matrix[i * m + j]));
        }
        if(n_k < n_i) 
            S = n_k;
        else
            S = n_i;
        //printf("%d\n", S);
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
            //printf("%c %c\n", matrix[i * m + l_i][j - x_i], matrix[k * m + l_k][j - x_k]);
            if(matrix[i * m + l_i][j - x_i] < matrix[k * m + l_k][j - x_k]) {
                k = i;
                break;
            }
        }
    }
    return k;
}
/*
Функция вычеркиванет из слова A_pq букв слова A_kq.
*/
/*void fun(char **matrix, int n, int m, int k){
    int a, s;
    char *q;
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            a = 0;
            if(i == k) 
            matrix[i * m + j][0] = '\n';
            else {
                s = 0;
                while(s < strlen(matrix[k * m + j])) {
                    if(q = (strpbrk(matrix[i * m + j] + (char *)s, matrix[k * m + j])) != NULL) {
                        for(int t = 0; t < strlen(matrix[k * m + j] + s)) {
                            matrix[i * m + j][s] = matrix[i * m + j][s + 1];
                        }
                    }
                    else s++;    
                }
            }
        }
    }
}*/


















