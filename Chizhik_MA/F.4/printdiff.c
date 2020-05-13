#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "printdiff.h"

/*
 * Колбэк-функция для qsort: возвращает отрицательное значение, если str1 < str2,
 * 0, если str1 и str2 совпадают, и положительное значение, если str1 > str2 
 * (используется лексикографический порядок)
*/

static int compare_strings(const void *str1, const void *str2) {
	return strcmp(*(char **)str1, *(char **)str2);
}

/* 
 * Вывод списка имен, присутствующих в первом массиве имен и отсутствующих во втором
 *
 * Параметры аналогичны функции print_sym_difference (нет только dir2_name).
*/

static void print_difference(FILE *output, 
		char **dir1, char *dir1_name, int dir1_len, 
		char **dir2, int dir2_len) {
	fprintf(output, "%s: ", dir1_name);
	for (int i = 0; i < dir1_len; i++) {
		unsigned int flag = 0;

		if ((i > 0) && (strcmp(dir1[i], dir1[i-1]) == 0)) {
			continue;
		}

		for (int j = 0; (j < dir2_len) /*&& (strcmp(dir1[i], dir2[j]) < 0)*/; j++) {
			if (strcmp(dir1[i], dir2[j]) == 0) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) {
			fprintf(output, "%s ", dir1[i]);
		}
	}
	fprintf(output, "\n");
}

void print_sym_difference(FILE *output,
		char **dir1, char *dir1_name, int dir1_len, 
		char **dir2, char *dir2_name, int dir2_len) {
	qsort(dir1, (size_t)dir1_len, sizeof(char *), compare_strings);
	qsort(dir2, (size_t)dir2_len, sizeof(char *), compare_strings);

	print_difference(output, dir1, dir1_name, dir1_len, dir2, dir2_len);
	print_difference(output, dir2, dir2_name, dir2_len, dir1, dir1_len);
}
